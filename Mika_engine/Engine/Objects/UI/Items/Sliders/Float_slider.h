#pragma once

#include "Slider.h"

class Float_slider : public Slider
{
    GENERATED_BODY(Float_slider)

public:
	Float_slider() noexcept;

	void draw() override;
};

