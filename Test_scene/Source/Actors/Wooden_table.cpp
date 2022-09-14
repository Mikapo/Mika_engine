#include "Wooden_table.h"
#include "Objects/Components/Scene_components/Mesh_component.h"
#include "Assets/Material.h"
#include "Assets/Asset_manager.h"

using namespace Mika_engine;

void Wooden_table::initialize()
{
	Actor::initialize();

	auto* table_mesh_component = create_component_cast<Mesh_component>(Mesh_component::static_class());
    auto mesh = get_asset_manager().get_mesh("Models/WoodenTable.obj");
    table_mesh_component->set_mesh(mesh);

    Material table_material;
    auto table_texture = get_asset_manager().get_texture("Textures/wooden_floor.png", OpenGL::Texture_slot::color);
    table_material.add_texture(table_texture);
    table_mesh_component->set_material(table_material);

	auto* plant_mesh_component = create_component_cast<Mesh_component>(Mesh_component::static_class());
    auto plant_mesh = get_asset_manager().get_mesh("Models/potted_plant.obj");
    plant_mesh_component->set_mesh(plant_mesh);

    Material plant_material;
    auto plant_texture = get_asset_manager().get_texture("Textures/potted_plant.jpg", OpenGL::Texture_slot::color);
    plant_material.add_texture(plant_texture);
    plant_mesh_component->set_material(plant_material);

	set_location({ 0.0f, 1.5f, 0.0f });
	plant_mesh_component->set_relative_location({ 0.25f, 0.0f, 0.55f });
}
