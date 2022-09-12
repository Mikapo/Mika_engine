#include "Ground.h"
#include <iostream>
#include "Objects/Components/Scene_components/Mesh_component.h"
#include "Rendering/Texture/Texture_slots.h"
#include "Core/Mika_engine.h"

void Ground::initialize()
{
	Actor::initialize();

	auto* mesh_component = create_component_cast<Mesh_component>(Mesh_component::static_class());
    auto mesh = get_asset_manager().get_mesh("Models/cube.obj");
    mesh_component->set_mesh(mesh);

	Material material;
    auto texture = get_asset_manager().get_texture("Textures/wooden_floor.png", OpenGL::Texture_slot::color);
    material.add_texture(texture);
    mesh_component->set_material(material);

	set_location({ 0.0f, 0.0f, -1.0f });
    set_scale({3.0f, 3.0f, 1.0f});
}

void Ground::update(float deltatime)
{
	Actor::update(deltatime);

	
}
