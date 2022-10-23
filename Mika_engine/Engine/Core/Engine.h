#pragma once

#include "Datatypes/Input.h"
#include "Garbage_collector.h"
#include "Rendering/Render_engine.h"
#include "Utility/Class_obj.h"
#include "Utility/Delegate.h"
#include <chrono>
#include <thread>

namespace MEngine
{
    class Object;
    class World;

    // Top level of engine
    class Engine
    {
    public:
        // Starts the engine
        void start();

        /**
         * Registers object to the engine and to the garbage collector
         *
         * @param object to be registered
         */
        void register_object(std::unique_ptr<Object> obj);

        [[nodiscard]] size_t get_amount_of_registered_objects() noexcept;

        /**
         * @return Is object is this valid object that is being tracked by garbage collector
         */
        [[nodiscard]] bool is_object_valid(const Object* obj) const;

        /**
         * @return Time that has passed between frames in ms
         */
        [[nodiscard]] float get_deltatime() const noexcept;

        void set_render_settings(Render_settings settings) noexcept;
        [[nodiscard]] Render_settings get_render_settings() const noexcept;

        /**
         * @param World that is created when engine starts
         */
        void set_default_world(Class_obj* world_class);

        /**
         * @param World that engine switches to
         */
        void set_world(const Class_obj* world_class);

        void set_window_title(std::string_view name);
        void log(std::string_view log, std::string_view group, Log_severity severity);

        // Delegate that broadcast when input happens
        Delegate<Input> m_on_input;

    private:
        // Main update loop for the engine
        void update_loop();

        // Cleanup that gets called when the engine closes
        void cleanup();

        // Updates m_deltatime variable with time that passed since last time this method was called
        void update_deltatime() noexcept;

        // Sends data for render engine to render which includes mesh locations for example
        void send_data_to_render_engine();

        void on_input(Input input);
        void setup_callbacks();

        Render_engine m_render_engine;
        Garbage_collector m_garbage_collector;
        World* m_world = nullptr;
        Class_obj* m_default_world = nullptr;

        bool m_has_started = false;

        float m_deltatime = 0.0f;
        std::chrono::steady_clock::time_point m_time_since_last_frame;

        std::vector<Input> m_inputs;
    };

} // namespace MEngine
