#include "Sofa.h"
#include "Assets/Material.h"
#include "Objects/Components/Scene_components/Mesh_component.h"

using namespace Mika_engine;

void Sofa::initialize()
{
    Actor::initialize();

    auto* mesh_component = create_component_cast<Mesh_component>(Mesh_component::static_class());
    mesh_component->set_mesh("Models/sofa.obj");

    Material material;
    material.add_texture("Textures/sofa.jpg");
    mesh_component->set_material(material);
}
