#include "Cube.h"
#include "Objects/Components/Scene_components/Collision_component.h"
#include "Objects/Components/Scene_components/Mesh_component.h"

using namespace Mika_engine;

void Cube::initialize()
{
    Actor::initialize();

    m_mesh_component = create_component_cast<Mika_engine::Mesh_component>(Mika_engine::Mesh_component::static_class());
    m_mesh_component->set_mesh("Engine/Engine_models/cube.obj");

    Material material;
    material.m_specular = {0.0f, 0.0f, 0.0f, 1.0f};
    m_mesh_component->set_material(material);

    create_component(Collision_component::static_class());
}

void Cube::set_color(glm::vec4 color)
{
    Material material = m_mesh_component->get_material();
    material.m_default_color = color;
    m_mesh_component->set_material(material);
}
