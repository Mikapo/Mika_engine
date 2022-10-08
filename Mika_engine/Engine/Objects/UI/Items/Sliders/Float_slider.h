#pragma once

#include "Slider.h"

namespace MEngine
{
    class Float_slider : public Slider
    {
        GENERATED_BODY(Float_slider)

    public:
        Float_slider() noexcept;

        void draw() override;
    };
} // namespace MEngine
