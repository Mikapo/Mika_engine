#pragma once

#include "Objects/Actor.h"

class Ground : public Mika_engine::Actor
{
    GENERATED_BODY(Ground)

public:
	void initialize() override;
};

