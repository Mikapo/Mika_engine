#include "Test_world.h"

#include "Actors/Ground.h"
#include "Actors/Light.h"
#include "Actors/Player.h"
#include "Actors/Sofa.h"
#include "Actors/Table.h"
#include "Actors/Wooden_table.h"
#include "UI/Settings_ui.h"

void Test_world::initialize()
{
    World::initialize();

    spawn_actor(Ground::static_class());
    spawn_actor(Sofa::static_class());
    spawn_actor(Table::static_class());
    spawn_actor(Wooden_table::static_class());
    spawn_actor(Light::static_class());

    auto* player = spawn_actor(Player::static_class());
    set_player_actor(player);

    auto* ui = create_ui(Settings_ui::static_class());
    ui->add_to_viewport(this);
}

void Test_world::update(float deltatime)
{
    MEngine::World::update(deltatime);
}
