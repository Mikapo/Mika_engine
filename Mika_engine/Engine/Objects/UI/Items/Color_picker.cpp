#include "Color_picker.h"

void Color_picker::draw()
{
	ImGui::ColorPicker4(get_name().data(), m_current_color.data(), m_flags);
}

void Color_picker::update(float deltatime)
{
	if (m_current_color != m_previously_checked_color)
	{
		m_on_color_change.call(glm::vec4(m_current_color[0], m_current_color[1], m_current_color[2], m_current_color[3]));
		m_previously_checked_color = m_current_color;
	}
}

void Color_picker::add_flag(ImGuiColorEditFlags flag)
{
	m_flags |= flag;
}
