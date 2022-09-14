#include "Color_picker.h"

namespace Mika_engine
{
    void Color_picker::draw()
    {
        ImGui::ColorPicker4(get_name().data(), m_current_color.data(), m_flags);
    }

    void Color_picker::update(float deltatime)
    {
        if (m_current_color != m_previously_checked_color)
        {
            m_on_color_change.broadcast(
                glm::vec4(m_current_color.at(0), m_current_color.at(1), m_current_color.at(2), m_current_color.at(3)));
            m_previously_checked_color = m_current_color;
        }
    }

    void Color_picker::add_flag(ImGuiColorEditFlags flag) noexcept
    {
        m_flags |= flag;
    }
} // namespace Mika_engine
