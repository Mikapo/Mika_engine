#pragma once

#include "Objects/Actor.h"

class Table : public Actor
{
public:
	void initialize() override;
	void update(float deltatime) override;
};

