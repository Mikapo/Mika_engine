#include "UI_renderer.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

namespace MEngine
{
    void UI_renderer::initialize(GLFWwindow* window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
        m_has_been_initialized = true;
    }

    void UI_renderer::cleanup()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        m_has_been_initialized = false;
    }

    void UI_renderer::render_ui()
    {
        if (!m_has_been_initialized)
            return;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (m_log_is_visible)
            render_log();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void UI_renderer::render_log()
    {
        ImGui::Begin("Log", &m_log_is_visible);

        for (Log_message& log : m_log)
            ImGui::Text(log.message.c_str());

        ImGui::End();
    }

    void UI_renderer::log(Log_message log_message)
    {
        m_log.push_back(std::move(log_message));
    }

    bool UI_renderer::is_log_visible() const noexcept
    {
        return m_log_is_visible;
    }

    void UI_renderer::set_log_visible(bool new_visibility) noexcept
    {
        m_log_is_visible = new_visibility;
    }

} // namespace MEngine
