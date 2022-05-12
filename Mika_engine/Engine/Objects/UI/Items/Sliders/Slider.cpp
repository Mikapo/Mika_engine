#include "Slider.h"

void Slider::update(float deltatime)
{
	if (m_current_value != m_last_checked_value)
	{
		m_on_slider_change.call(m_current_value);
		m_last_checked_value = m_current_value;
	}
}

void Slider::set_max(float max)
{
	m_max = max;
}

void Slider::set_min(float min)
{
	m_min = min;
}

void Slider::set_format(std::string_view format)
{
	m_format = format;
}

void Slider::set_value(float value)
{
	m_current_value = value;
}
