#include "Collision_component.h"
#include "Objects/World.h"
#include "Utility/Collisions/Colliders/Oriented_bounding_box.h"
#include "Utility/Collisions/Colliders/Sphere.h"

namespace MEngine
{
    Collision_component::Collision_component() noexcept
    {
        m_collider = std::make_shared<Oriented_bounding_box>();
    }

    void Collision_component::set_collider_type(Collider_type type)
    {
        if (type == m_current_collider_type)
            return;

        m_current_collider_type = type;

        switch (type)
        {
        case Collider_type::obb:
            m_collider = std::make_shared<Oriented_bounding_box>();
            break;
        case Collider_type::sphere:
            m_collider = std::make_shared<Sphere>();
            break;
        default:
            throw std::invalid_argument("invalid enum");
        }
    }

    void Collision_component::initialize()
    {
        Scene_component::initialize();

        get_world()->register_collision_component(m_collider, this);
        get_owner()->register_collision(this);
    }

    bool Collision_component::is_overlapping(const Collision_component* other) const
    {
        return m_collider->is_overlapping(other->m_collider.get()).has_value();
    }

    std::optional<Hit_result> Collision_component::is_overlapping_with_line(const Line& line) const
    {
        return m_collider->is_overlapping_with_line(line);
    }

    bool Collision_component::check_for_collisions()
    {
        const auto collision = get_world()->find_collisions(m_collider.get(), this);
        m_previous_collision = collision.value_or(Collision_result());
        return collision.has_value();
    }

    Collision_result Collision_component::get_previous_collision() const noexcept
    {
        return m_previous_collision;
    }

    void Collision_component::update_world_transform()
    {
        Scene_component::update_world_transform();

        m_collider->update(get_world_transform());
        get_world()->update_collisions(m_collider, this);
    }

} // namespace MEngine
