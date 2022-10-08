#pragma once

#include "Objects/Actor.h"

class Ground : public MEngine::Actor
{
    GENERATED_BODY(Ground)

public:
    void initialize() override;
};
