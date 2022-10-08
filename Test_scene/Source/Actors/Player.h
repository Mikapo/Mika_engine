#pragma once

#include "Objects/Actor.h"

class Player : public MEngine::Actor
{
    GENERATED_BODY(Player)

public:
    void initialize() override;

private:
    void setup_input();
    void move_forward(float input);
    void move_right(float input);
    void rotate(float input);

    float movement_speed = 2.0f;
};
