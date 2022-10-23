#include "Bullet.h"
#include "Objects/Components/Scene_components/Collision_component.h"
#include "Objects/Components/Scene_components/Mesh_component.h"
#include "Objects/World.h"

void Bullet::initialize()
{
    Actor::initialize();

    auto* mesh_component = create_component_cast<MEngine::Mesh_component>(MEngine::Mesh_component::static_class());
    mesh_component->set_mesh("Engine/Engine_models/Sphere.obj");

    m_collision = create_component_cast<MEngine::Collision_component>(MEngine::Collision_component::static_class());
    m_collision->set_collider_type(MEngine::Collider_type::sphere);
    set_scale({0.05f, 0.05f, 0.05f});

    m_on_collision_detected.add_object(this, &Bullet::on_collision);
    set_lifetime(10.0f);
}

void Bullet::update(float deltatime)
{
    Actor::update(deltatime);

    const glm::vec3 gravity = glm::vec3(0.0f, 0.0f, -0.19f) * deltatime;
    // m_velocity += gravity;

    add_world_offset(m_velocity * deltatime, true);
}

void Bullet::on_collision(MEngine::Collision_result collision)
{
   
}
