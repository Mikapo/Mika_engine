#pragma once

#include "Objects/Actor.h"

class Collision_component;
class Cube : public Actor
{
    GENERATED_BODY(Cube)

public:
    void initialize() override;
    void update(float deltatime) override;

    Collision_component* m_collision = nullptr;
};
