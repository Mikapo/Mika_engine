#pragma once

#include "Objects/Actor.h"

class Ground : public Actor
{
public:
	void initialize() override;
	void update(float deltatime) override;
};

