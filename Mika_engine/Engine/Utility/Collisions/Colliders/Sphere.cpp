#include "Sphere.h"

#include "Utility/Collisions/Collision_algorithms.h"
#include <stdexcept>

namespace Mika_engine
{
    float Sphere::get_radius() const noexcept
    {
        return m_radius;
    }

    void Sphere::update(Transform transform)
    {
        Collider::update(transform);

        const glm::vec3 scale = transform.m_scale;
        m_radius = glm::max(glm::max(scale.x, scale.y), scale.z);
        m_extend = glm::vec3(m_radius);
    }

    std::optional<Collision_result> Sphere::is_overlapping(const Collider* collider) const
    {
        if (!collider)
            throw std::invalid_argument("collision is null");

        return collider->is_overlapping_with_sphere(*this);
    }

    std::optional<Hit_result> Sphere::is_overlapping_with_line(const Line& line) const
    {
        return Collision_algorithms::line_and_sphere(line, *this);
    }

    std::optional<Collision_result> Sphere::is_overlapping_with_obb(const Oriented_bounding_box& collider) const
    {
        return Collision_algorithms::obb_and_sphere(collider, *this);
    }

    std::optional<Collision_result> Sphere::is_overlapping_with_sphere(const Sphere& collider) const
    {
        return Collision_algorithms::sphere_and_sphere(collider, *this);
    }

}
