#pragma once

#include "Objects/Actor.h"

class Collision_component;
class Bullet : public Actor
{
    GENERATED_BODY(Bullet)

public:
    void initialize() override;
    void update(float deltatime) override;
    glm::vec3 m_velocity;

private:
    void on_collision(Collision_component* this_component, Collision_component* other_component);

    Collision_component* m_collision = nullptr;
};
