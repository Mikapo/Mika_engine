#include "Collision_component.h"
#include "Objects/World.h"
#include "Utility/Collisions/Oriented_bounding_box.h"


Collision_component::Collision_component() 
{ 
    m_collision = std::make_shared<Oriented_bounding_box>(); 
}

void Collision_component::initialize() 
{ 
	get_world()->register_collision_component(m_collision, this); 
	Scene_component::initialize();
}

bool Collision_component::is_overlapping(Collision_component* other) const
{
    return m_collision->is_overlapping(other->m_collision.get());
}

std::optional<Hit_result> Collision_component::is_overlapping_with_line(const Line& line) const
{
    return m_collision->is_overlapping_with_line(line);
}

std::optional<Collision_component*> Collision_component::check_for_collisions(std::optional<Transform> owner_transform)
{
    std::optional<Collision_component*> collision;

    if (owner_transform.has_value())
    {
        Oriented_bounding_box box = calculate_component_world_transform(owner_transform.value());
        collision = get_world()->find_collisions(&box, this);
    }
    else
        collision = get_world()->find_collisions(m_collision.get(), this);

	return collision;
}

void Collision_component::update_world_transform() 
{ 
	Scene_component::update_world_transform(); 
	
	m_collision->update(get_world_transform());
    get_world()->update_collisions(m_collision, this);
}
