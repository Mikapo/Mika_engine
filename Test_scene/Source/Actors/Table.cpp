#include "Table.h"
#include <iostream>
#include "Objects/Components/Scene_components/Mesh_component.h"
#include "Assets/Material.h"
#include "Assets/Asset_manager.h"

void Table::initialize()
{
	Actor::initialize();

	auto* mesh_component = create_component_cast<Mesh_component>(Mesh_component::static_class());
    auto mesh = get_asset_manager().get_mesh("Models/round_wooden_table.obj");
    mesh_component->set_mesh(mesh);

	Material material;
    auto texture = get_asset_manager().get_texture("Textures/round_wooden_table.jpg", OpenGL::Texture_slot::color);
    material.add_texture(texture);
    mesh_component->set_material(material);

	set_location({ -2.0f, 2.0f, 0.0f });
}

void Table::update(float deltatime)
{
	Actor::update(deltatime);

	
}
