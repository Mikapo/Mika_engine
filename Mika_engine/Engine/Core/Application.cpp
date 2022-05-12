#include "Application.h"
#include "Debug/Debug_logger.h"
#include <iostream>



void Application::start()
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

void Application::stop() { m_has_started = false; }

void Application::get_window_dimensions(int32_t& out_width, int32_t& out_height) const
{ 
    out_width = m_width;
    out_height = m_height;
}

void Application::init()
{
    glfwInit();

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_SAMPLES, 4);
    m_window = glfwCreateWindow(m_width, m_height, m_name.c_str(), NULL, NULL);

    if (!m_window)
    {
        glfwTerminate();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);

    glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSwapInterval(1);
    glfwSetWindowUserPointer(get_window(), this);
    setup_callbacks();
    on_window_open_callback->call(m_window);
}

void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const GLchar* msg, const void* data)
{
    Debug_logger::get().log_OpenGL(source, type, id, severity, length, msg, data);
}

void Application::on_window_resize(GLFWwindow* window, int32_t new_width, int32_t new_height)
{
    m_width = new_width;
    m_height = new_height;

    if (m_window_resize_callback)
        m_window_resize_callback->call(new_width, new_height);
}

void Application::on_key_event(int32_t key, int32_t scancode, int32_t action, int32_t mods)
{
    if (m_on_key_event_callback)
        m_on_key_event_callback->call(key, scancode, action, mods);
}

void Application::setup_callbacks() const
{
    auto on_key = [](GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
    {
        if (action == GLFW_PRESS || action == GLFW_RELEASE)
            static_cast<Application*>(glfwGetWindowUserPointer(window))->on_key_event(key, scancode, action, mods);
    };
    glfwSetKeyCallback(get_window(), on_key);


    auto on_resize = [](GLFWwindow* window, int32_t new_width, int32_t new_height)
    {
        static_cast<Application*>(glfwGetWindowUserPointer(window))->on_window_resize(window, new_width, new_height);
    };
    glfwSetWindowSizeCallback(get_window(), on_resize);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugMessageCallback, NULL);
}

void Application::render_loop()
{
    while (!glfwWindowShouldClose(m_window) && m_has_started)
    {
        glViewport(0, 0, m_width, m_height);
        glfwPollEvents();
        glDepthMask(GL_TRUE);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glClearColor(m_background_color.r, m_background_color.b, m_background_color.g, m_background_color.a);

        if (m_render_callback)
            m_render_callback->call();

        glfwSwapBuffers(m_window);
    }
}

void Application::cleanup()
{
    if (m_cleanup_callback)
        m_cleanup_callback->call();

    glfwDestroyWindow(m_window);
    glfwTerminate();
    m_window = nullptr;
}
