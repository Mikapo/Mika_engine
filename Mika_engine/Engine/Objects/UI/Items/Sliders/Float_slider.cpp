#include "Float_slider.h"

namespace Mika_engine
{
    Float_slider::Float_slider() noexcept
    {
        m_format = "%.0f";
    }

    void Float_slider::draw()
    {
        ImGui::SliderFloat(get_name().data(), &m_current_value, m_min, m_max, m_format.c_str());
    }
} // namespace Mika_engine
