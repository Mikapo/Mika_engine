#pragma once

#include "Objects/Actor.h"

namespace Mika_engine
{
    class Light_component;
}

class Light : public Mika_engine::Actor
{
    GENERATED_BODY(Light)

public:
	void initialize() override;
	void change_light_color(glm::vec4 color);

private:
	Mika_engine::Light_component* m_light_component;
};

