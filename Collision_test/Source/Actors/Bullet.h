#pragma once

#include "Objects/Actor.h"

class Bullet : public MEngine::Actor
{
    GENERATED_BODY(Bullet)

public:
    void initialize() override;
    void update(float deltatime) override;
    glm::vec3 m_velocity;

private:
    void on_collision(MEngine::Collision_result collision);

    MEngine::Collision_component* m_collision = nullptr;
};
