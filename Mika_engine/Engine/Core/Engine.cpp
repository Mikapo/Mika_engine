#include "Engine.h"
#include "Datatypes/Frame_data.h"
#include "Objects/Object.h"
#include "Objects/World.h"
#include <mutex>
#include <stdexcept>

namespace MEngine
{
    void Engine::start()
    {
        m_has_started = true;
        setup_callbacks();
        m_render_engine.start_render_thread();
        set_world(m_default_world);
        log("Engine starting", "Engine", Log_severity::notification);
        update_loop();
        cleanup();
    }

    void Engine::setup_callbacks()
    {
        m_render_engine.m_on_input.add_object(this, &Engine::on_input);
    }

    void Engine::register_object(std::unique_ptr<Object> obj)
    {
        m_garbage_collector.register_object(std::move(obj));
    }

    size_t Engine::get_amount_of_registered_objects() noexcept
    {
        return m_garbage_collector.get_registered_objects().size();
    }

    bool Engine::is_object_valid(const Object* obj) const
    {
        return m_garbage_collector.is_object_valid(obj);
    }

    float Engine::get_deltatime() const noexcept
    {
        return m_deltatime;
    }

    void Engine::set_render_settings(Render_settings settings) noexcept
    {
        m_render_engine.set_render_settings(settings);
    }

    Render_settings Engine::get_render_settings() const noexcept
    {
        return m_render_engine.get_render_settings();
    }

    void Engine::set_default_world(Class_obj* world_class)
    {
        if (!world_class)
            throw std::invalid_argument("world_class was null");

        m_default_world = world_class;
    }

    void Engine::set_window_title(std::string_view name)
    {
        m_render_engine.set_window_title(name);
    }

    void Engine::update_deltatime() noexcept
    {
        using namespace std::chrono;

        const auto time = high_resolution_clock::now();
        const auto time_passed = time - m_time_since_last_frame;
        m_time_since_last_frame = time;
        const float delta_microseconds = static_cast<float>(duration_cast<microseconds>(time_passed).count());

        // Converts to ms
        m_deltatime = delta_microseconds * 0.000001F;
    }

    void Engine::log(std::string_view log, std::string_view group, Log_severity severity)
    {
        std::string log_string = std::format("[{}] {}", log, group);
        m_render_engine.add_log_message({std::move(log_string), severity});
    }

    void Engine::on_input(Input input)
    {
        m_on_input.broadcast(input);
    }

    void Engine::set_world(const Class_obj* world_class)
    {
        if (!m_has_started)
            throw std::runtime_error("Should not be called when engine has not started");

        if (world_class == nullptr)
            return;

        m_world = m_default_world->construct_cast<World>(this);
        if (m_world == nullptr)
            return;

        m_garbage_collector.set_root_object(m_world);
        m_world->initialize();
    }

    void Engine::send_data_to_render_engine()
    {
        Frame_data frame;

        if (is_object_valid(m_world))
            m_world->get_frame_data(frame);

        m_render_engine.add_frame(std::move(frame));
    }

    void Engine::update_loop()
    {
        while (m_render_engine.is_running())
        {
            m_render_engine.wait_until(0, 2);
            update_deltatime();
            m_garbage_collector.update();
            m_render_engine.poll_events();

            if (is_object_valid(m_world))
                m_world->update(m_deltatime);

            send_data_to_render_engine();
        }
    }

    void Engine::cleanup()
    {
        log("Starting cleanup", "Engine", Log_severity::notification);

        m_has_started = false;

        m_render_engine.join_render_thread();
        m_garbage_collector.cleanup();

        log("Shutting down engine", "Engine", Log_severity::notification);
    }
} // namespace MEngine
