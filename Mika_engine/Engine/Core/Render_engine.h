#pragma once

#include "Datatypes/Frame_data.h"
#include "Rendering/Application/Application.h"
#include "Scene_renderer.h"
#include "Utility/Thread_safe_deque.h"
#include "Datatypes/Input.h"
#include <string_view>
#include <thread>
#include "Utility/Delegate.h"

namespace Mika_engine
{
    class Render_engine
    {
    public:
        void start_render_thread();
        void join_with_render_thread();
        bool is_running() const noexcept;
        void set_window_title(std::string_view title);
        void set_render_settings(Render_settings settings) noexcept;
        Render_settings get_render_settings() const noexcept;
        size_t frames_in_queue() const;
        void add_frame(Frame_data frame);
        void poll_events();

        Delegate<Input> m_on_input;

    private:
        void start_application();
        void render();
        void on_window_resize(int32_t width, int32_t height);
        void update_window_size(int32_t width, int32_t height);
        void on_input(Input_key key, Input_action action);
        void on_window_open();

        bool m_is_running = false;
        int32_t m_window_width = 0, m_window_height = 0;
        float m_aspect_ratio = 0;

        OpenGL::Application m_application;
        Scene_renderer m_scene_renderer;
        std::thread m_thread_handle;

        std::condition_variable m_frame_conditional;
        std::mutex m_frame_mutex;
        Thread_safe_deque<Frame_data> m_frame_queue;

        Thread_safe_deque<Input> m_inputs;
    };
} // namespace Mika_engine
