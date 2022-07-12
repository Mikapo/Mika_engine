#pragma once

#include "Objects/Actor.h"

class Table : public Actor
{
    GENERATED_BODY(Table)

public:
	void initialize() override;
	void update(float deltatime) override;
};

