#pragma once

#include <unordered_set>

struct GLFWwindow;

namespace Mika_engine
{
    class Engine;
    class UI;
    class UI_renderer
    {
    public:
        void initialize(GLFWwindow* window, Engine* engine);
        void cleanup();
        void render_ui(std::unordered_set<UI*>& viewport);

    private:
        Engine* m_engine = nullptr;
        bool m_has_been_initialized = false;
    };
}


