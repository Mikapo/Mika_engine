#include "Mika_engine.h"

#include "Datatypes/Frame_data.h"
#include "Debug/Debug_logger.h"
#include "Objects/Object.h"
#include "Objects/World.h"
#include "Scene_renderer.h"
#include <iostream>
#include <mutex>
#include <stdexcept>

void Mika_engine::start()
{
    LOG(notification, engine, "Mika engine starting");

    setup_callbacks();
    m_update_thread = std::thread([this] { update_thread(); });
    m_has_started = true;
    m_application.start();
}

void Mika_engine::setup_callbacks()
{
    m_application.set_on_window_open_callback(this, &Mika_engine::on_window_open);
    m_application.set_render_callback(this, &Mika_engine::render_thread);
    m_application.set_cleanup_callback(this, &Mika_engine::cleanup);
    m_application.set_on_key_event_callback(this, &Mika_engine::on_key_event);
    m_application.set_window_resize_callback(this, &Mika_engine::on_window_resize);
}

void Mika_engine::on_window_open(GLFWwindow* window)
{
    m_application.get_window_dimensions(m_window_width, m_window_height);
    m_aspect_ratio = static_cast<float>(m_window_width) / static_cast<float>(m_window_height);
    m_scene_renderer.update_window_size(m_window_width, m_window_height);
    m_ui_renderer.initialize(window, this);
    m_scene_renderer.initialize(this);
}

void Mika_engine::register_object(std::unique_ptr<Object> obj)
{
    m_garbage_collector.register_object(std::move(obj));
}

size_t Mika_engine::get_amount_of_registered_objects() noexcept
{
    return m_garbage_collector.get_registered_objects().size();
}

bool Mika_engine::is_object_valid(const Object* obj) const
{
    return m_garbage_collector.is_object_valid(obj);
}

float Mika_engine::get_deltatime() const noexcept
{
    return m_deltatime;
}

Asset_manager& Mika_engine::get_asset_manager() noexcept
{
    return m_asset_manager;
}

void Mika_engine::get_window_dimensions(int32_t& width, int32_t& height) const noexcept
{
    width = m_window_width;
    height = m_window_height;
}

float Mika_engine::get_screen_aspect_ratio() const noexcept
{
    if (m_window_width < 1.0f || m_window_height < 1.0f)
        return 0.0f;
    else
        return m_aspect_ratio;
}

void Mika_engine::set_render_settings(Render_settings settings) noexcept
{
    m_scene_renderer.set_render_settings(settings);
}

Render_settings Mika_engine::get_render_settings() const noexcept
{
    return m_scene_renderer.get_render_settings();
}

void Mika_engine::set_default_world(Class_obj* world_class)
{
    if (!world_class)
        throw std::invalid_argument("world_class was null");

    m_default_world = world_class;
}

void Mika_engine::set_window_title(std::string_view name)
{
    m_application.set_window_title(name);
}

void Mika_engine::set_window_dimensions(int32_t width, int32_t height) noexcept
{
    m_application.set_window_dimensions(width, height);
}

void Mika_engine::update_deltatime() noexcept
{
    using namespace std::chrono;

    const auto time = high_resolution_clock::now();
    const auto time_passed = time - m_time_since_last_frame;
    const float deltatime = static_cast<float>(time_passed.count()) * 0.000000001f;
    m_time_since_last_frame = time;
    m_deltatime = deltatime;
}

void Mika_engine::on_window_resize(int32_t width, int32_t height) noexcept
{
    m_window_width = width;
    m_window_height = height;
    m_aspect_ratio = static_cast<float>(m_window_width) / static_cast<float>(m_window_height);
    m_scene_renderer.update_window_size(width, height);
}

static std::mutex input_mutex;
void Mika_engine::on_key_event(Input_key key, Input_action action)
{
    std::lock_guard<std::mutex> lock(input_mutex);
    m_inputs.emplace_back(key, action);
}

void Mika_engine::handle_inputs()
{
    std::lock_guard<std::mutex> lock(input_mutex);

    for (Input& input : m_inputs)
        m_on_key_event.broadcast(input);

    m_inputs.clear();
}

void Mika_engine::set_world(Class_obj* world_class)
{
    if (!m_has_started)
        throw std::runtime_error("should not be called when engine has not started");

    m_world = m_default_world->construct_cast<World>(this);
    if (!m_world)
        return;

    m_garbage_collector.set_root_object(m_world);
    m_world->initialize();
}

void Mika_engine::update_thread()
{
    if (m_default_world)
        set_world(m_default_world);

    m_time_since_last_frame = std::chrono::high_resolution_clock::now();

    while (!m_update_thread_stop_flag)
    {
        if (m_scene_renderer.frames_in_queue() > 2)
            continue;

        m_garbage_collector.update();
        update_deltatime();
        handle_inputs();

        if (is_object_valid(m_world))
        {
            m_world->update(m_deltatime);

            Frame_data frame;
            m_world->get_frame_data(frame);
            m_scene_renderer.new_frame(std::move(frame));
        }
    }
}

void Mika_engine::render_thread()
{
    m_scene_renderer.render_frame();

    if (is_object_valid(m_world))
        m_ui_renderer.render_ui(m_world->get_viewport());
}

void Mika_engine::cleanup()
{
    LOG(notification, engine, "Staring cleanup");

    m_has_started = false;
    m_update_thread_stop_flag = true;
    m_update_thread.join();
    m_garbage_collector.cleanup();
    m_scene_renderer.cleanup();
    m_ui_renderer.cleanup();
    m_asset_manager.cleanup();

    LOG(notification, engine, "Exiting mika engine");

#ifdef _DEBUG
    Debug_logger::get().write_to_log_file();
#endif
}
