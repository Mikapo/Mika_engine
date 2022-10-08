#pragma once

#include "Slider.h"

namespace MEngine
{
    class Angle_slider : public Slider
    {
        GENERATED_BODY(Angle_slider)

    public:
        Angle_slider() noexcept;

        void draw() override;
    };
} // namespace MEngine
