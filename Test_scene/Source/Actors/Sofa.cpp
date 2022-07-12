#include "Sofa.h"
#include <iostream>
#include "Objects/Components/Scene_components/Mesh_component.h"
#include "Rendering/Shading/Material.h"
#include "Assets/Asset_manager.h"

void Sofa::initialize()
{
	Actor::initialize();

	auto*mesh_component = create_component_cast<Mesh_component>(Mesh_component::static_class());
    auto mesh = get_asset_manager().get_mesh("Models/sofa.obj");
    mesh_component->set_mesh(mesh);

    Material material;
    auto texture = get_asset_manager().get_texture("Textures/sofa.jpg");
    material.add_texture(texture, Texture_slot::texture);
    mesh_component->set_material(material);
}

void Sofa::update(float deltatime)
{
	Actor::update(deltatime);

	
}
