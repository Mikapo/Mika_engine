#pragma once

#include "../UI_item.h"
#include "Utility/Delegate.h"
#include <string>

namespace Mika_engine
{
    class Slider : public UI_item
    {
        GENERATED_BODY(Slider)

    public:
        void update(float deltatime) override;
        void set_max(float max) noexcept;
        void set_min(float min) noexcept;
        void set_format(std::string_view format);
        void set_value(float value) noexcept;

        Delegate<float> m_on_slider_change;

    protected:
        float m_max = 360.f, m_min = -360.0f;
        std::string m_format = "%.0f";
        float m_current_value = 0.0f;

    private:
        float m_last_checked_value = 0.0f;
    };
} // namespace Mika_engine
