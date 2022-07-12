#pragma once

#include "Objects/Actor.h"

class Ground : public Actor
{
    GENERATED_BODY(Ground)

public:
	void initialize() override;
	void update(float deltatime) override;
};

