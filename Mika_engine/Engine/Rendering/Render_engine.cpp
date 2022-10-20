#include "Render_engine.h"
#include <stdexcept>

namespace MEngine
{
    void Render_engine::start_render_thread()
    {
        if (!m_is_running)
        {
            m_is_running = true;
            m_thread_handle = std::thread([this] { start_application(); });
        }
        else
            throw std::logic_error("Thread was already running");
    }

    void Render_engine::join_render_thread()
    {
        if (m_thread_handle.joinable())
            m_thread_handle.join();
    }

    void Render_engine::render()
    {
        std::unique_lock lock(m_frame_mutex);
        m_frame_conditional.wait(lock, [this] { return frames_in_queue() > 1; });

        m_scene_renderer.render_frame(m_frame_queue.pop_front());

        if (!m_new_logs.empty())
            m_ui_renderer.log(m_new_logs.pop_front());

        m_ui_renderer.render_ui();
    }

    void Render_engine::on_window_resize(int32_t width, int32_t height)
    {
        update_window_size(width, height);
    }

    void Render_engine::update_window_size(int32_t width, int32_t height)
    {
        m_window_width = width;
        m_window_height = height;

        m_aspect_ratio = static_cast<float>(m_window_width) / static_cast<float>(m_window_height);
        m_scene_renderer.update_window_size(m_window_width, m_window_height);
    }

    void Render_engine::on_input(Input_key key, Input_action action)
    {
        if (key == Input_key::L && action == Input_action::press)
            m_ui_renderer.set_log_visible(!m_ui_renderer.is_log_visible());

        m_inputs.push_back(Input(key, action));
    }

    void Render_engine::start_application()
    {
        m_application.m_on_render.set_callback(this, &Render_engine::render);
        m_application.m_on_window_open.set_callback(this, &Render_engine::on_window_open);
        m_application.m_on_window_rezise.set_callback(this, &Render_engine::on_window_resize);
        m_application.m_on_input.set_callback(this, &Render_engine::on_input);
        m_application.m_on_cleanup.set_callback(this, &Render_engine::cleanup);

        m_application.start();
        m_is_running = false;
    }

    void Render_engine::on_window_open()
    {
        m_scene_renderer.initialize();
        m_ui_renderer.initialize(m_application.get_window());

        int32_t window_width = 0, window_height = 0;
        m_application.get_window_dimensions(window_width, window_height);
        update_window_size(window_width, window_height);
    }

    void Render_engine::cleanup()
    {
        m_scene_renderer.cleanup();
        m_ui_renderer.cleanup();
    }

    bool Render_engine::is_running() const noexcept
    {
        return m_is_running;
    }

    void Render_engine::set_window_title(std::string_view title)
    {
        m_application.set_window_title(title);
    }

    void Render_engine::set_render_settings(Render_settings settings) noexcept
    {
        m_scene_renderer.set_render_settings(settings);
    }

    Render_settings Render_engine::get_render_settings() const noexcept
    {
        return m_scene_renderer.get_render_settings();
    }

    size_t Render_engine::frames_in_queue() const
    {
        return m_frame_queue.size();
    }

    void Render_engine::add_frame(Frame_data frame)
    {
        m_frame_conditional.notify_one();
        m_frame_queue.push_back(std::move(frame));
    }

    void Render_engine::add_log_message(Log_message log_message)
    {
        m_new_logs.push_back(std::move(log_message));
    }

    void Render_engine::poll_events()
    {
        while (!m_inputs.empty())
            m_on_input.broadcast(m_inputs.pop_front());
    }
} // namespace MEngine
