#pragma once

#include "Objects/Object.h"
#include "ImGui/imgui.h"
#include <string>

class UI_item : public Object
{
    GENERATED_BODY(UI_item)

public:
    virtual void draw() {}
	void set_name(const std::string& name);
	std::string_view get_name() const;

private:
	std::string m_name = "default name";
};
