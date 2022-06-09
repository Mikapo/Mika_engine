#include "Cube.h"

#include "Objects/Components/Scene_components/Mesh_component.h"
#include "Objects/Components/Scene_components/Collision_component.h"
#include "Objects/World.h"
#include "Bullet.h"
#include "Assets/Asset_manager.h"
#include "Player.h"
#include "Objects/World.h"
#include "Utility/Collisions/Line.h"
#include <iostream>

void Cube::initialize() 
{ 
	Actor::initialize();

	auto* mesh_component = create_component_cast<Mesh_component>(Mesh_component::static_class()); 
	auto cube_mesh = get_asset_manager().get_mesh("Engine/Engine_models/cube.obj");
    mesh_component->set_mesh(cube_mesh);

	m_collision = create_component_cast<Collision_component>(Collision_component::static_class());
}

void Cube::update(float deltatime) 
{
	Actor::update(deltatime);

	static Player* player = nullptr;
    if (!player)
        player = get_world()->find_actor_of_class<Player>();

	const glm::vec3 start = player->get_location();
    const glm::vec3 end = player->get_location() + player->get_forward_vector() * 2000.0f;

	static int32_t overlap_amount = 0;

	if (m_collision->is_overlapping_with_line({.m_start = start, .m_end = end}))
        std::cout << "overlapping " << ++overlap_amount << "\n";
} 
