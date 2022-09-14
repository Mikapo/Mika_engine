#pragma once

#include "Slider.h"

namespace Mika_engine
{
    class Float_slider : public Slider
    {
        GENERATED_BODY(Float_slider)

    public:
        Float_slider() noexcept;

        void draw() override;
    };
}


