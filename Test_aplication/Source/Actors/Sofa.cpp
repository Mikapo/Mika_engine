#include "Sofa.h"
#include <iostream>
#include "Objects/Components/Scene_components/Mesh_component.h"
#include "Rendering/Shading/Material.h"

void Sofa::initialize()
{
	Actor::initialize();

	Mesh_component* mesh = create_component<Mesh_component>();
	mesh->load_mesh_from_file("Models/sofa.obj");
	Material material;
	material.add_texture_from_file("Textures/sofa.jpg", Texture_slot::texture);
	mesh->set_material_to_current_mesh(material);
}

void Sofa::update(float deltatime)
{
	Actor::update(deltatime);

	
}
