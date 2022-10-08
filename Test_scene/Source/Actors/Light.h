#pragma once

#include "Objects/Actor.h"

namespace MEngine
{
    class Light_component;
}

class Light : public MEngine::Actor
{
    GENERATED_BODY(Light)

public:
    void initialize() override;
    void change_light_color(glm::vec4 color);

private:
    MEngine::Light_component* m_light_component;
};
