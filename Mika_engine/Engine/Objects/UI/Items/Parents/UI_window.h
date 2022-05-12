#pragma once

#include "UI_parent.h"

class UI_window : public UI_parent
{
public:
	void draw() override;
	void add_flag(ImGuiWindowFlags flag);

private:
	bool m_open = true;
	ImGuiWindowFlags m_flags;
};

