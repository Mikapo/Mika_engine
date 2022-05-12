#include "Actor_component.h"

void Actor_component::set_owner(Actor* owner)
{
	m_owning_actor = owner;
}

Actor* Actor_component::get_owner() const
{
	return m_owning_actor;
}

void Actor_component::set_world(World* world)
{
	m_owning_world = world;
}

World* Actor_component::get_world() const
{
	return m_owning_world;
}

