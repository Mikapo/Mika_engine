#define GLEW_STATIC

#include "GL/glew.h"

#include "Application.h"
#include <stdexcept>

void OpenGL::Application::start()
{
    if (!m_has_started)
    {
        m_has_started = true;
        init();
        render_loop();
        cleanup();
        m_has_started = false;
    }
}

GLFWwindow* OpenGL::Application::get_window() const noexcept
{
    return m_window;
}

void OpenGL::Application::get_window_dimensions(int32_t& out_width, int32_t& out_height) const noexcept
{
    out_width = m_width;
    out_height = m_height;
}

void OpenGL::Application::init()
{
    glfwInit();

    // Create a windowed mode window and its OpenGL context
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    m_window = glfwCreateWindow(m_width, m_height, m_name.c_str(), nullptr, nullptr);

    if (m_window == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("Window was not correctly created");
    }

    // Make the window's context current
    glfwMakeContextCurrent(m_window);

    // limiting render framerate to screens framerame
    glfwSwapInterval(1);

    glfwSetWindowUserPointer(get_window(), this);

    glewInit();
    setup_opengl_settings();
    setup_callbacks();

    m_on_window_open.broadcast();
}

void OpenGL::Application::setup_opengl_settings() noexcept
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_TRUE);
}

void OpenGL::Application::on_window_resize([[maybe_unused]] GLFWwindow* window, int32_t new_width, int32_t new_height)
{
    m_width = new_width;
    m_height = new_height;

    m_on_window_rezise.broadcast(new_width, new_height);
}

void OpenGL::Application::on_key_event(
    int32_t key, [[maybe_unused]] int32_t scancode, int32_t action, [[maybe_unused]] int32_t mods)
{
    m_on_input.broadcast(static_cast<Input_key>(key), static_cast<Input_action>(action));
}

void OpenGL::Application::set_window_dimensions(int32_t width, int32_t height) noexcept
{
    m_width = width;
    m_height = height;

    if (m_window != nullptr)
        glfwSetWindowSize(m_window, width, height);
}

void OpenGL::Application::set_window_background_color(Window_background_color new_color) noexcept
{
    m_background_color = new_color;
}

void OpenGL::Application::set_window_title(std::string_view name)
{
    m_name = name;
}

void OpenGL::Application::setup_callbacks() const noexcept
{
    auto on_key = [](GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods) {
        static_cast<Application*>(glfwGetWindowUserPointer(window))->on_key_event(key, scancode, action, mods);
    };
    glfwSetKeyCallback(get_window(), on_key);

    auto on_resize = [](GLFWwindow* window, int32_t new_width, int32_t new_height) {
        static_cast<Application*>(glfwGetWindowUserPointer(window))->on_window_resize(window, new_width, new_height);
    };
    glfwSetWindowSizeCallback(get_window(), on_resize);
}

void OpenGL::Application::render_loop()
{
    while (glfwWindowShouldClose(m_window) == 0)
    {
        glViewport(0, 0, m_width, m_height);
        glfwPollEvents();
        glClearColor(m_background_color.r, m_background_color.b, m_background_color.g, m_background_color.a);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        m_on_render.broadcast();
        glfwSwapBuffers(m_window);
    }
}

void OpenGL::Application::cleanup()
{
    m_on_cleanup.broadcast();
    glfwDestroyWindow(m_window);
    glfwTerminate();

    m_window = nullptr;
}
