#include "Wooden_table.h"
#include <iostream>
#include "Objects/Components/Scene_components/Mesh_component.h"
#include "Rendering/Shading/Material.h"

void Wooden_table::initialize()
{
	Actor::initialize();

	Mesh_component* table_mesh = create_component<Mesh_component>();
	table_mesh->load_mesh_from_file("Models/WoodenTable.obj");
	Material table_material;
	table_material.add_texture_from_file("Textures/wooden_floor.png", Texture_slot::texture);
	table_mesh->set_material_to_current_mesh(table_material);

	Mesh_component* plant_mesh = create_component<Mesh_component>();
	plant_mesh->load_mesh_from_file("Models/potted_plant.obj");
	Material plant_material;
	plant_material.add_texture_from_file("Textures/potted_plant.jpg", Texture_slot::texture);
	plant_mesh->set_material_to_current_mesh(plant_material);

	set_location({ 0.0f, 1.5f, 0.0f });
	plant_mesh->set_relative_location({ 0.25f, 0.0f, 0.55f });
}

void Wooden_table::update(float deltatime)
{
	Actor::update(deltatime);

	
}
