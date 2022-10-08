#include "Table.h"
#include "Assets/Material.h"
#include "Objects/Components/Scene_components/Mesh_component.h"

using namespace Mika_engine;

void Table::initialize()
{
    Actor::initialize();

    auto* mesh_component = create_component_cast<Mesh_component>(Mesh_component::static_class());
    mesh_component->set_mesh("Models/round_wooden_table.obj");

    Material material;
    material.add_texture("Textures/round_wooden_table.jpg");
    mesh_component->set_material(material);

    set_location({-2.0f, 2.0f, 0.0f});
}
