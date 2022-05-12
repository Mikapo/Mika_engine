#pragma once

#include "Objects/Actor.h"

class Wooden_table : public Actor
{
public:
	void initialize() override;
	void update(float deltatime) override;
};

