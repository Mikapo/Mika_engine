#pragma once

#include "Objects/Actor.h"

class Light_component;
class Light : public Actor
{
    GENERATED_BODY(Light)

public:
	void initialize() override;
	void change_light_color(glm::vec4 color);

private:
	Light_component* m_light_component;
};

