#pragma once

#include "Objects/Actor.h"

class Light : public MEngine::Actor
{
    GENERATED_BODY(Light)

public:
    void initialize() override;
};
