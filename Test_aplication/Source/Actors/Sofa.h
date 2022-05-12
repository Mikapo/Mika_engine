#pragma once

#include "Objects/Actor.h"

class Sofa : public Actor
{
public:
	void initialize() override;
	void update(float deltatime) override;
};

