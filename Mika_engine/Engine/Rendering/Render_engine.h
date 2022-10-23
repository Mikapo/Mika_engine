#pragma once

#include "Datatypes/Frame_data.h"
#include "Datatypes/Input.h"
#include "OpenGL/Application/Application.h"
#include "Scene_renderer.h"
#include "UI_renderer.h"
#include "Utility/Delegate.h"
#include "Utility/Thread_safe_deque.h"
#include <string_view>
#include <thread>

namespace MEngine
{
    class Render_engine
    {
    public:
        // Starts rendering on new thread
        void start_render_thread();

        void join_render_thread();

        /**
         * @return Is render thread running
         */
        [[nodiscard]] bool is_running() const noexcept;

        void set_render_settings(Render_settings settings) noexcept;
        [[nodiscard]] Render_settings get_render_settings() const noexcept;

        // Adds new frame to queue to be rendered
        void add_frame(Frame_data frame);

        // Adds new log to queue to be added to log window
        void add_log_message(Log_message log_message);

        void poll_events();
        void wait_until(
            int32_t min_frames_behind, int32_t max_frames_behind = std::numeric_limits<int32_t>::max()) noexcept;
        void set_window_title(std::string_view title);

        Delegate<Input> m_on_input;

    private:
        void start_application();
        void update_window_size(int32_t width, int32_t height);

        // Events from application
        void render();
        void on_window_resize(int32_t width, int32_t height);
        void on_input(Input_key key, Input_action action);
        void on_window_open();
        void cleanup();

        bool m_is_running = false;
        int32_t m_window_width = 0, m_window_height = 0;
        float m_aspect_ratio = 0;

        OpenGL::Application m_application;
        Scene_renderer m_scene_renderer;
        UI_renderer m_ui_renderer;
        std::thread m_thread_handle;

        std::condition_variable m_wait_until_conditional;
        std::mutex m_wait_until_mutex;

        Thread_safe_deque<Frame_data> m_frame_queue;
        Thread_safe_deque<Input> m_inputs;
        Thread_safe_deque<Log_message> m_new_logs;
    };
} // namespace MEngine
