#include "Collision_algorithms.h"

#include "Oriented_bounding_box.h"
#include "Line.h"

bool Collision_algorithms::obb_and_obb(const Oriented_bounding_box& a, const Oriented_bounding_box& b)
{
    const auto& a_normals = a.get_normals();
    const auto& b_normals = b.get_normals();

    const std::array<glm::vec3, 15> axises
    {
        a_normals[0],
        a_normals[1],
        a_normals[2],
        b_normals[0],
        b_normals[1],
        b_normals[2],
        glm::cross(a_normals[0], b_normals[0]),
        glm::cross(a_normals[0], b_normals[1]),
        glm::cross(a_normals[0], b_normals[2]),
        glm::cross(a_normals[1], b_normals[0]),
        glm::cross(a_normals[1], b_normals[1]),
        glm::cross(a_normals[1], b_normals[2]),
        glm::cross(a_normals[2], b_normals[0]),
        glm::cross(a_normals[2], b_normals[1]),
        glm::cross(a_normals[2], b_normals[2]),
    };

    return sat_algorithm(a.get_vertices(), b.get_vertices(), axises);
}

bool Collision_algorithms::line_and_obb(const Line& line, const Oriented_bounding_box& box) 
{ 
    const glm::mat4 inverse_model = glm::inverse(box.get_model());
    const glm::vec3 start = inverse_model * glm::vec4(line.m_start, 1.0f);
    const glm::vec3 end = inverse_model * glm::vec4(line.m_end, 1.0f);
    const Line local_line = {.m_start = start, .m_end = end};

    const bool interesection = line_and_aabb(local_line, glm::vec3(-1.0f), glm::vec3(1.0f));
    
    return interesection;
}

bool Collision_algorithms::line_and_aabb(const Line& Line, glm::vec3 box_min, glm::vec3 box_max) { return false; }

float Collision_algorithms::project_point_to_axis(glm::vec3 point, glm::vec3 axis)
{
    axis = glm::normalize(axis);
    return glm::dot(point, axis);
}
