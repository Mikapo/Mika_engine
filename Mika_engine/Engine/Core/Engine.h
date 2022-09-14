#pragma once

#include "Assets/Asset_manager.h"
#include "Datatypes/Input.h"
#include "Garbage_collector.h"
#include "Utility/Class_obj.h"
#include "Utility/Delegate.h"
#include "Render_engine.h"
#include <chrono>
#include <thread>

namespace Mika_engine
{
    class Mesh_data;
    class Light_data;
    class Camera_data;
    class Object;
    class World;

    class Engine
    {
    public:
        void start();
        void register_object(std::unique_ptr<Object> obj);
        size_t get_amount_of_registered_objects() noexcept;
        bool is_object_valid(const Object* obj) const;
        float get_deltatime() const noexcept;
        Asset_manager& get_asset_manager() noexcept;
        void set_render_settings(Render_settings settings) noexcept;
        Render_settings get_render_settings() const noexcept;
        void set_default_world(Class_obj* world_class);
        void set_world(Class_obj* world_class);
        void set_window_title(std::string_view name);

        Delegate<Input> m_on_key_event;

    private:
        void update_loop();
        void cleanup();
        void update_deltatime() noexcept;
        void on_key_event(Input_key key, Input_action action);
        void handle_inputs();
        void setup_callbacks();

        Render_engine m_render_engine;
        Garbage_collector m_garbage_collector;
        Asset_manager m_asset_manager;
        World* m_world = nullptr;
        Class_obj* m_default_world = nullptr;

        bool m_has_started = false;
        float m_deltatime = 0.0f;
        std::chrono::steady_clock::time_point m_time_since_last_frame;
        std::vector<Input> m_inputs;
    };

}
