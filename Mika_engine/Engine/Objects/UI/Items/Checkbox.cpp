#include "Checkbox.h"

void Checkbox::draw()
{
	ImGui::Checkbox(get_name().data(), &m_is_checked);
}

void Checkbox::update(float deltatime)
{
	if (m_is_checked != m_was_checked_in_last_check)
	{
		m_on_checked_change.call(m_is_checked);
		m_was_checked_in_last_check = m_is_checked;
	}
}

void Checkbox::set_checked(bool checked)
{
	m_is_checked = checked;
}
