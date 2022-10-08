#include "Ground.h"
#include "Core/Engine.h"
#include "Objects/Components/Scene_components/Mesh_component.h"

using namespace Mika_engine;

void Ground::initialize()
{
    Actor::initialize();

    auto* mesh_component = create_component_cast<Mesh_component>(Mesh_component::static_class());
    mesh_component->set_mesh("Models/cube.obj");

    Material material;
    material.add_texture("Textures/wooden_floor.png");
    mesh_component->set_material(material);

    set_location({0.0f, 0.0f, -1.0f});
    set_scale({3.0f, 3.0f, 1.0f});
}
