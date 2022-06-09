#include "Collision_test_world.h"
#include "Actors/Player.h"
#include "Actors/Light.h"
#include "Actors/Cube.h"

void Collision_test_world::initialize() 
{ 
	World::initialize();

	auto* player = spawn_actor(Player::static_class());
    player->set_location({0.0f, 0.0f, 0.5f});
    set_player_actor(player);

	auto* light = spawn_actor(Light::static_class());
    light->set_location({0.0f, 0.0f, 3.0f}); 

	setup_walls();
}

void Collision_test_world::setup_walls() 
{ 
    auto* cube_class = Cube::static_class();
    auto* cube = spawn_actor(cube_class);
    cube->set_location({0.0f, 0.0f, -0.5f});
    cube->set_scale({2.0f, 2.0f, 0.25f});

	cube = spawn_actor(cube_class);
    cube->set_location({2.0f, 0.0f, 0.75f});
    cube->set_scale({0.1f, 2.0f, 1.5f});
}
