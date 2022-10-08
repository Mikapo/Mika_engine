#include "Table.h"
#include "Assets/Material.h"
#include "Objects/Components/Scene_components/Mesh_component.h"

void Table::initialize()
{
    Actor::initialize();

    auto* mesh_component = create_component_cast<MEngine::Mesh_component>(MEngine::Mesh_component::static_class());
    mesh_component->set_mesh("Models/round_wooden_table.obj");

    MEngine::Material material;
    material.add_texture("Textures/round_wooden_table.jpg");
    mesh_component->set_material(material);

    set_location({-2.0f, 2.0f, 0.0f});
}
