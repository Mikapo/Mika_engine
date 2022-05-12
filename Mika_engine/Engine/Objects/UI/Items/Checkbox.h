#pragma once

#include "UI_item.h"
#include "Utility/Delegate.h"

class Checkbox : public UI_item
{
public:
	void draw() override;
	void update(float deltatime) override;
	void set_checked(bool checked);

	Delegate<bool> m_on_checked_change;

private:
	bool m_is_checked = false;
	bool m_was_checked_in_last_check = false;
};

