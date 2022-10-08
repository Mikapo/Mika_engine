#pragma once

#include "Objects/Actor.h"

class Player : public Mika_engine::Actor
{
    GENERATED_BODY(Player)

public:
    void initialize() override;

private:
    void setup_input();
    void move_forward(float input);
    void move_right(float input);
    void rotate(float input);
    void shoot();

    float m_movement_speed = 2.0f;
};
