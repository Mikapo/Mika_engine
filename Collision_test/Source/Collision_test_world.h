#pragma once

#include "Objects/World.h"

class Collision_test_world : public MEngine::World
{
    GENERATED_BODY(Collision_test_world)

public:
    void initialize() override;

private:
    void setup_walls();
};
