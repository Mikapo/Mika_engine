#include "Test_world.h"

#include "Actors/Sofa.h"
#include "Actors/Player.h"
#include "Actors/Table.h"
#include "Actors/Ground.h"
#include "Actors/Light.h"
#include "Actors/Wooden_table.h"
#include "UI/SettingsUI.h"

#include <iostream>

void Test_world::initialize()
{
	World::initialize();

	spawn_actor<Ground>();
	spawn_actor<Sofa>();
	spawn_actor<Table>();
	spawn_actor<Wooden_table>();
	spawn_actor<Light>();

	auto* player = spawn_actor<Player>();
	set_player_actor(player);

	auto* ui = create_ui<SettingsUI>();
	ui->add_to_viewport(this);
}

void Test_world::update(float deltatime)
{
	World::update(deltatime);

}
