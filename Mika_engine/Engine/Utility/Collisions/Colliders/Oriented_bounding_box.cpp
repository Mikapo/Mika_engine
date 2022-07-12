#include "Oriented_bounding_box.h"
#include "Utility/Collisions/Collision_algorithms.h"
#include <stdexcept>

const std::array<glm::vec3, 8> Oriented_bounding_box::m_box_vertices = {
    glm::vec3(1.0f, 1.0f, 1.0f),    glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, 1.0f),
    glm::vec3(-1.0f, 1.0f, 1.0f),   glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, 1.0f, -1.0f)};

Oriented_bounding_box::Oriented_bounding_box(Transform transform) noexcept
{
    update(transform);
}

void Oriented_bounding_box::update(Transform transform)
{
    Collider::update(transform);

    m_transform = transform;

    const Directional_vectors normals = transform.m_rotation.calculate_directional_vectors_from_rotation();
    m_normals = {normals.m_forward, normals.m_right, normals.m_up};

    m_extend = glm::vec3(-std::numeric_limits<float>::infinity());
    const glm::mat4 model = get_model();

    for (size_t i = 0; i < m_box_vertices.size(); ++i)
    {
        m_vertices.at(i) = model * glm::vec4(m_box_vertices.at(i), 1.0f);
        m_extend = glm::abs(glm::max(m_vertices.at(i) - get_origin(), m_extend));
    }
}

std::optional<Collision_result> Oriented_bounding_box::is_overlapping(const Collider* collider) const
{
    if (!collider)
        throw std::invalid_argument("other is null");

    return collider->is_overlapping_with_obb(*this);
}

std::optional<Hit_result> Oriented_bounding_box::is_overlapping_with_line(const Line& line) const
{
    return Collision_algorithms::line_and_obb(line, *this);
}

std::optional<Collision_result> Oriented_bounding_box::is_overlapping_with_obb(
    const Oriented_bounding_box& collider) const
{
    return Collision_algorithms::obb_and_obb(*this, collider);
}

std::optional<Collision_result> Oriented_bounding_box::is_overlapping_with_sphere(const Sphere& collider) const
{
    return Collision_algorithms::obb_and_sphere(*this, collider);
}

const std::array<glm::vec3, 8>& Oriented_bounding_box::get_vertices() const noexcept
{
    return m_vertices;
}

const std::array<glm::vec3, 3>& Oriented_bounding_box::get_normals() const noexcept
{
    return m_normals;
}

Transform Oriented_bounding_box::get_transform() const noexcept
{
    return m_transform;
}
