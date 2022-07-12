#pragma once

#include "Objects/Actor.h"

class Sofa : public Actor
{
    GENERATED_BODY(Sofa)

public:
	void initialize() override;
	void update(float deltatime) override;
};

