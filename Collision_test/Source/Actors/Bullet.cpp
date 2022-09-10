#include "Bullet.h"

#include "Assets/Asset_manager.h"
#include "Objects/Components/Scene_components/Collision_component.h"
#include "Objects/Components/Scene_components/Mesh_component.h"
#include "Objects/World.h"

void Bullet::initialize()
{
    Actor::initialize();

    auto* mesh_component = create_component_cast<Mesh_component>(Mesh_component::static_class());
    auto mesh = get_asset_manager().get_mesh("Engine/Engine_models/Sphere.obj");
    mesh_component->set_mesh(mesh);

    m_collision = create_component_cast<Collision_component>(Collision_component::static_class());
    m_collision->set_collider_type(Collider_type::sphere);
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

void Bullet::on_collision(Collision_result collision)
{
    glm::vec3 start = get_location();
    glm::vec3 end = collision.m_other_component->get_world_transform().m_location;

    auto hit_result = get_world()->line_trace(start, end, {this});

    if (hit_result.has_value())
    {
        glm::vec3 hit_normal = hit_result.value().m_normal;
        glm::vec3 new_velocity = glm::reflect(m_velocity, hit_normal);
        m_velocity = new_velocity;
    }
    else
        m_velocity *= -1;
}
