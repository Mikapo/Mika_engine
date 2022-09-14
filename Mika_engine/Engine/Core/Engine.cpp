#include "Engine.h"
#include "Datatypes/Frame_data.h"
#include "Debug/Debug_logger.h"
#include "Objects/Object.h"
#include "Objects/World.h"
#include "Scene_renderer.h"
#include <iostream>
#include <mutex>
#include <stdexcept>

namespace Mika_engine
{
    void Engine::start()
    {
        LOG(notification, engine, "Mika engine starting");

        m_has_started = true;
        setup_callbacks();
        m_render_engine.start_render_thread();

        if (m_default_world)
            set_world(m_default_world);

        update_loop();
        cleanup();
    }

    void Engine::setup_callbacks()
    {
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

    Asset_manager& Engine::get_asset_manager() noexcept
    {
        return m_asset_manager;
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
        const float deltatime = static_cast<float>(time_passed.count()) * 0.000000001f;
        m_time_since_last_frame = time;
        m_deltatime = deltatime;
    }

    static std::mutex input_mutex;
    void Engine::on_key_event(Input_key key, Input_action action)
    {
        std::lock_guard<std::mutex> lock(input_mutex);
        m_inputs.emplace_back(key, action);
    }

    void Engine::handle_inputs()
    {
        std::lock_guard<std::mutex> lock(input_mutex);

        for (Input& input : m_inputs)
            m_on_key_event.broadcast(input);

        m_inputs.clear();
    }

    void Engine::set_world(Class_obj* world_class)
    {
        if (!m_has_started)
            throw std::runtime_error("Should not be called when engine has not started");

        m_world = m_default_world->construct_cast<World>(this);
        if (!m_world)
            return;

        m_garbage_collector.set_root_object(m_world);
        m_world->initialize();
    }

    void Engine::update_loop()
    {
        while (m_render_engine.is_running())
        {
            if (m_render_engine.frames_in_queue() > 2)
                continue;

            m_garbage_collector.update();
            update_deltatime();
            m_render_engine.poll_events();

            if (is_object_valid(m_world))
            {
                m_world->update(m_deltatime);

                Frame_data frame;
                m_world->get_frame_data(frame);
                m_render_engine.add_frame(std::move(frame));
            }
        }
    }

    void Engine::cleanup()
    {
        LOG(notification, engine, "Staring cleanup");

        m_has_started = false;

        m_render_engine.join_with_render_thread();
        m_garbage_collector.cleanup();
        m_asset_manager.cleanup();

        LOG(notification, engine, "Exiting mika engine");

#ifdef _DEBUG
        Debug_logger::get().write_to_log_file();
#endif
    }
} // namespace Mika_engine
