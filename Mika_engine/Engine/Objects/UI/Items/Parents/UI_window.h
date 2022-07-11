#pragma once

#include "UI_parent.h"

class UI_window : public UI_parent
{
    GENERATED_BODY(UI_window)

public:
	void draw() override;
    void add_flag(ImGuiWindowFlags flag) noexcept;

private:
	bool m_open = true;
    ImGuiWindowFlags m_flags = ImGuiWindowFlags_::ImGuiWindowFlags_None;
};

