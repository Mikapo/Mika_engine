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
    Cube* floor = spawn_actor_cast<Cube>(cube_class);
    floor->set_location({0.0f, 0.0f, -0.5f});
    floor->set_scale({4.0f, 4.0f, 0.1f});
    floor->set_color({0.2f, 0.2f, 0.2f, 1.0f});

	Actor* wall = spawn_actor(cube_class);
    wall->set_location({4.1f, 0.0f, 0.9f});
    wall->set_scale({0.1f, 4.0f, 1.5f});

    wall = spawn_actor(cube_class);
    wall->set_location({-4.1f, 0.0f, 0.9f});
    wall->set_scale({0.1f, 4.0f, 1.5f});

    wall = spawn_actor(cube_class);
    wall->set_location({0.0f, 4.1f, 0.9f});
    wall->set_rotation({0.0f, 90.0f, 0.0f});
    wall->set_scale({0.1f, 4.0f, 1.5f});

    wall = spawn_actor(cube_class);
    wall->set_location({0.0f, -4.1f, 0.9f});
    wall->set_rotation({0.0f, 90.0f, 0.0f});
    wall->set_scale({0.1f, 4.0f, 1.5f});
}
