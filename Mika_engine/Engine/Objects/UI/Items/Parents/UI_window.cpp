#include "UI_window.h"

namespace MEngine
{
    void UI_window::draw()
    {
        ImGui::Begin(get_name().data(), &m_open, m_flags);
        draw_children();
        ImGui::End();
    }

    void UI_window::add_flag(ImGuiWindowFlags flag) noexcept
    {
        m_flags |= flag;
    }
} // namespace MEngine
