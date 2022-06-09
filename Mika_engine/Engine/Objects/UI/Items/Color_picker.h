#pragma once

#include "UI_item.h"
#include "Utility/Delegate.h"
#include <array>
#include "glm/vec4.hpp"

class Color_picker : public UI_item
{
    GENERATED_BODY(Color_picker)

public:
	void draw() override;
	void update(float deltatime) override;
	void add_flag(ImGuiColorEditFlags flag);

	Delegate<glm::vec4> m_on_color_change;

private:
	ImGuiColorEditFlags m_flags;

	std::array<float, 4> m_current_color; 
	std::array<float, 4> m_previously_checked_color;
};

