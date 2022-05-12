#include "Table.h"
#include <iostream>
#include "Objects/Components/Scene_components/Mesh_component.h"
#include "Rendering/Shading/Material.h"

void Table::initialize()
{
	Actor::initialize();

	Mesh_component* mesh = create_component<Mesh_component>();
	mesh->load_mesh_from_file("Models/round_wooden_table.obj");
	Material material;
	material.add_texture_from_file("Textures/round_wooden_table.jpg", Texture_slot::texture);
	mesh->set_material_to_current_mesh(material);

	set_location({ -2.0f, 2.0f, 0.0f });
}

void Table::update(float deltatime)
{
	Actor::update(deltatime);

	
}
