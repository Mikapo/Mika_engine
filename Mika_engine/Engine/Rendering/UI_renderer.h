#pragma once

#include "Datatypes/Log_severity.h"
#include <unordered_set>

struct GLFWwindow;

namespace MEngine
{
    struct Log_message
    {
        std::string message;
        Log_severity severity;
    };

    class UI_renderer
    {
    public:
        void initialize(GLFWwindow* window);
        void cleanup();
        void render_ui();

        void log(Log_message log_message);
        [[nodiscard]] bool is_log_visible() const noexcept;
        void set_log_visible(bool new_visibility) noexcept;

    private:
        void render_log();

        bool m_log_is_visible = false;
        bool m_has_been_initialized = false;
        std::vector<Log_message> m_log;
    };
} // namespace MEngine
