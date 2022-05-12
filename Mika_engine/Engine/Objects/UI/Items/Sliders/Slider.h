#pragma once

#include <string>
#include "Utility/Delegate.h"
#include "../UI_item.h"

class Slider : public UI_item
{
public:
	void update(float deltatime) override;
	void set_max(float max);
	void set_min(float min);
	void set_format(std::string_view format);
	void set_value(float value);

	Delegate<float> m_on_slider_change;

protected:
	float m_max = 360.f, m_min = -360.0f;
	std::string m_format = "%.0f";
	float m_current_value = 0.0f;

private:
	float m_last_checked_value = 0.0f;
};

