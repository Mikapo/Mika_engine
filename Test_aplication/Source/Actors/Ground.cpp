#include "Ground.h"
#include <iostream>
#include "Objects/Components/Scene_components/Mesh_component.h"

void Ground::initialize()
{
	Actor::initialize();

	Mesh_component* mesh = create_component<Mesh_component>();
	mesh->load_mesh_from_file("Models/ground.obj");

	Material material;
	material.add_texture_from_file("Textures/wooden_floor.png", Texture_slot::texture);
	mesh->set_material_to_current_mesh(material);

	set_location({ 0.0f, 0.0f, -1.0f });
}

void Ground::update(float deltatime)
{
	Actor::update(deltatime);

	
}
