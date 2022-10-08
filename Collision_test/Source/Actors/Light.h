#pragma once

#include "Objects/Actor.h"

class Light : public Mika_engine::Actor
{
    GENERATED_BODY(Light)

public:
    void initialize() override;
};
