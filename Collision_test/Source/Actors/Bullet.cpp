#include "Bullet.h"

#include "Objects/Components/Scene_components/Mesh_component.h"
#include "Objects/Components/Scene_components/Collision_component.h"
#include "Assets/Asset_manager.h"
#include "Utility/Collisions/Line.h"
#include <iostream>
#include <string>
#include "Core/Mika_engine.h"

void Bullet::initialize() 
{ 
	Actor::initialize(); 

	auto* mesh_component = create_component_cast<Mesh_component>(Mesh_component::static_class());
    auto mesh = get_asset_manager().get_mesh("Engine/Engine_models/Cube.obj");
    mesh_component->set_mesh(mesh);

	m_collision = create_component_cast<Collision_component>(Collision_component::static_class());
	set_scale({0.05f, 0.05f, 0.05f});
    set_lifetime(10.0f);

    m_on_collision_detected.add_object(this, &Bullet::on_collision);
}

void Bullet::update(float deltatime) 
{ 
	Actor::update(deltatime); 

    add_world_offset(m_velocity * deltatime, true);
}

void Bullet::on_collision(Collision_component* this_component, Collision_component* other_component)
{
    m_velocity *= -1;
}
