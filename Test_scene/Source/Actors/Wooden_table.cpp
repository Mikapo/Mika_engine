#include "Wooden_table.h"
#include "Assets/Material.h"
#include "Objects/Components/Scene_components/Mesh_component.h"

using namespace Mika_engine;

void Wooden_table::initialize()
{
    Actor::initialize();

    auto* table_mesh_component = create_component_cast<Mesh_component>(Mesh_component::static_class());
    table_mesh_component->set_mesh("Models/WoodenTable.obj");

    Material table_material;
    table_material.add_texture("Textures/wooden_floor.png");
    table_mesh_component->set_material(table_material);

    auto* plant_mesh_component = create_component_cast<Mesh_component>(Mesh_component::static_class());
    plant_mesh_component->set_mesh("Models/potted_plant.obj");

    Material plant_material;
    plant_material.add_texture("Textures/potted_plant.jpg");
    plant_mesh_component->set_material(plant_material);

    set_location({0.0f, 1.5f, 0.0f});
    plant_mesh_component->set_relative_location({0.25f, 0.0f, 0.55f});
}
