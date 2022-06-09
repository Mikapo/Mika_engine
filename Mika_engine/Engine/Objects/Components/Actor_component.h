#pragma once

#include "../Object.h"
#include "Datatypes/Transform.h"

class Actor;
class World;
class Actor_component : public Object
{
    GENERATED_BODY(Actor_component)

public:
	void set_owner(Actor* owner);
	Actor* get_owner() const;
	void set_world(World* world);
	World* get_world() const;

private:
	World* m_owning_world = nullptr;
	Actor* m_owning_actor = nullptr;

};

