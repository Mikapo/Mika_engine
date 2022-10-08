#include "Angle_slider.h"

namespace MEngine
{
    Angle_slider::Angle_slider() noexcept
    {
        m_format = "%.0f deg";
    }

    void Angle_slider::draw()
    {
        ImGui::SliderAngle(get_name().data(), &m_current_value, m_min, m_max, m_format.c_str());
    }
} // namespace MEngine
