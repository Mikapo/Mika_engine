#pragma once

#include "Objects/World.h"

class Collision_test_world : public Mika_engine::World
{
    GENERATED_BODY(Collision_test_world)

public:
    void initialize() override;

private:
    void setup_walls();
};
