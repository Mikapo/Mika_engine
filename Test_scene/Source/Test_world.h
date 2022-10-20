#pragma once

#include "Objects/World.h"

class Test_world : public MEngine::World
{
    GENERATED_BODY(Test_world)

public:
    void initialize() override;
    void update(float deltatime) override;
};
