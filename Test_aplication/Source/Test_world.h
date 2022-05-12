#pragma once

#include "Objects/World.h"

class Test_world : public World
{
public:
	void initialize() override;
	void update(float deltatime) override;
};

