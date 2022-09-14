#pragma once

#include "Objects/World.h"

class Test_world : public Mika_engine::World
{
    GENERATED_BODY(Test_world)

public:
	void initialize() override;
};

