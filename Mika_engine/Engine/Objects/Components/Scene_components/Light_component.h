#pragma once

#include "Scene_component.h"
#include "Datatypes/Frame_data.h"

class Light_component : public Scene_component
{
    GENERATED_BODY(Light_component)

public:
	void initialize() override;
	void set_color(glm::vec4 color);
	Light_data get_light_data();

private:
	glm::vec4 m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
};

