#pragma once

#include "Objects/Actor.h"

class Light_component;
class Light : public Actor
{
    GENERATED_BODY(Light)

public:
	void initialize() override;
};

