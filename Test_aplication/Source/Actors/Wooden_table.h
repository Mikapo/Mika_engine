#pragma once

#include "Objects/Actor.h"

class Wooden_table : public Actor
{
    GENERATED_BODY(Wooden_table)

public:
	void initialize() override;
	void update(float deltatime) override;
};

