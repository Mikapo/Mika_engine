#include "Sofa.h"
#include "Assets/Material.h"
#include "Objects/Components/Scene_components/Mesh_component.h"

void Sofa::initialize()
{
    Actor::initialize();

    auto* mesh_component = create_component_cast<MEngine::Mesh_component>(MEngine::Mesh_component::static_class());
    mesh_component->set_mesh("Models/sofa.obj");

    MEngine::Material material;
    material.add_texture("Textures/sofa.jpg");
    mesh_component->set_material(material);
}
