#include "Cube.h"
#include "Objects/Components/Scene_components/Collision_component.h"
#include "Objects/Components/Scene_components/Mesh_component.h"

void Cube::initialize()
{
    Actor::initialize();

    m_mesh_component = create_component_cast<MEngine::Mesh_component>(MEngine::Mesh_component::static_class());
    m_mesh_component->set_mesh("Engine/Engine_models/cube.obj");

    MEngine::Material material;
    material.m_specular = {0.0f, 0.0f, 0.0f, 1.0f};
    m_mesh_component->set_material(material);

    create_component(MEngine::Collision_component::static_class());
}

void Cube::set_color(glm::vec4 color)
{
    MEngine::Material material = m_mesh_component->get_material();
    material.m_default_color = color;
    m_mesh_component->set_material(material);
}
