#pragma once

#include "Slider.h"

namespace Mika_engine
{
    class Angle_slider : public Slider
    {
        GENERATED_BODY(Angle_slider)

    public:
        Angle_slider() noexcept;

        void draw() override;
    };
} // namespace Mika_engine
