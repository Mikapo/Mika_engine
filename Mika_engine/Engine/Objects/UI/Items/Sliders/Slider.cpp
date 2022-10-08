#include "Slider.h"

namespace MEngine
{
    void Slider::update(float deltatime)
    {
        if (m_current_value != m_last_checked_value)
        {
            m_on_slider_change.broadcast(m_current_value);
            m_last_checked_value = m_current_value;
        }
    }

    void Slider::set_max(float max) noexcept
    {
        m_max = max;
    }

    void Slider::set_min(float min) noexcept
    {
        m_min = min;
    }

    void Slider::set_format(std::string_view format)
    {
        m_format = format;
    }

    void Slider::set_value(float value) noexcept
    {
        m_current_value = value;
    }
} // namespace MEngine
