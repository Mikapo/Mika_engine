#include "Oriented_bounding_box.h"
#include "Collision_algorithms.h"

const std::array<glm::vec3, 8> Oriented_bounding_box::m_box_vertices = 
{
    glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, 1.0f),
    glm::vec3(-1.0f, 1.0f, 1.0f),  glm::vec3(1.0f, 1.0f, -1.0f),  glm::vec3(1.0f, -1.0f, -1.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, 1.0f, -1.0f)
};

Oriented_bounding_box::Oriented_bounding_box(Transform transform) 
{ 
    update(transform); 
}

void Oriented_bounding_box::update(Transform transform) 
{
    m_origin = transform.m_location;

    Directional_vectors normals = transform.m_rotation.calculate_directional_vectors_from_rotation();
    m_normals = {normals.m_forward, normals.m_right, normals.m_up};

    m_model = transform.calculate_model();

    m_extend = glm::vec3(-std::numeric_limits<float>::infinity());

    for (size_t i = 0; i < m_box_vertices.size(); ++i)
    {
       m_vertices[i] = m_model * glm::vec4(m_box_vertices[i], 1.0f);
       m_extend = glm::abs(glm::max(m_vertices[i], m_extend));
    }
}

glm::mat4 Oriented_bounding_box::get_model() const 
{ 
    return m_model; 
}

bool Oriented_bounding_box::is_overlapping(const Collision* other) const
{ 
    return other->is_overlapping_with_obb(this); 
}

std::optional<Hit_result> Oriented_bounding_box::is_overlapping_with_line(const Line& line) const
{
    return Collision_algorithms::line_and_obb(line, *this);
}

bool Oriented_bounding_box::is_overlapping_with_obb(const Oriented_bounding_box* other) const
{
   return Collision_algorithms::obb_and_obb(*this, *other);
}

const std::array<glm::vec3, 8>& Oriented_bounding_box::get_vertices() const
{ 
    return m_vertices; 
}

const std::array<glm::vec3, 3>& Oriented_bounding_box::get_normals() const
{ 
    return m_normals; 
}

Axis_comparison_result Oriented_bounding_box::compare_to_axis(glm::vec3 axis_origin, Axis axis) const
{
    float value_to_compare = 0.0f;
    Min_max box_min_max = {0.0f, 0.0f};

    switch (axis)
    {
    case Axis::x:
        value_to_compare = axis_origin.x;
        box_min_max = {.m_min = m_origin.x - m_extend.x, .m_max = m_origin.x + m_extend.x};
        break;
    case Axis::y:
        value_to_compare = axis_origin.y;
        box_min_max = {.m_min = m_origin.y - m_extend.y, .m_max = m_origin.y + m_extend.y};
        break;
    case Axis::z:
        value_to_compare = axis_origin.z;
        box_min_max = {.m_min = m_origin.z - m_extend.z, .m_max = m_origin.z + m_extend.z};
        break;
    }

    if (value_to_compare < box_min_max.m_min && value_to_compare < box_min_max.m_max)
        return Axis_comparison_result::right;
    else if (value_to_compare > box_min_max.m_min && value_to_compare > box_min_max.m_max)
        return Axis_comparison_result::left;
    else
        return Axis_comparison_result::overlap;
}




