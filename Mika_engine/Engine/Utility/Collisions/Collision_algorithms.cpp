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

std::optional<Hit_result> Collision_algorithms::line_and_obb(const Line& line, const Oriented_bounding_box& box)
{ 
    const glm::mat4 model = box.get_model();
    const glm::mat4 inverse_model = glm::inverse(model);
    const glm::vec4 local_start = inverse_model * glm::vec4(line.m_start, 1.0f);
    const glm::vec4 dir = glm::vec4((line.m_end - line.m_start), 0.0f);
    const glm::vec4 local_dir = glm::normalize(inverse_model * dir);

    std::optional<Hit_result> hit_result = ray_and_aabb(local_start, local_dir, glm::vec3(-1.0f), glm::vec3(1.0f));

    if (hit_result.has_value())
    {
        const glm::mat4 transpose = glm::transpose(inverse_model);
        glm::vec3& normal = hit_result.value().m_normal; 
        normal = transpose * glm::vec4(normal, 1.0f);
        normal = glm::normalize(normal);

        glm::vec3& hit_point = hit_result.value().m_hit_point;
        hit_point = model * glm::vec4(hit_point, 1.0f);

        float& lenght = hit_result.value().m_lenght;
        lenght = glm::length(hit_point - line.m_start);

        if (lenght > line.get_lenght())
            return std::optional<Hit_result>();
    }
    
    return hit_result;
}

std::optional<Hit_result> Collision_algorithms::ray_and_aabb(
    glm::vec3 start, glm::vec3 dir, glm::vec3 box_min, glm::vec3 box_max)
{ 
    const glm::vec3 tmin = (box_min - start) / dir;
    const glm::vec3 tmax = (box_max - start) / dir;
    const glm::vec3 sc = glm::min(tmin, tmax);
    const glm::vec3 sf = glm::max(tmin, tmax);
    const float first_intersection = glm::max(glm::max(sc.x, sc.y), sc.z);
    const float second_intersection = glm::min(glm::min(sf.x, sf.y), sf.z);

    if (!(first_intersection <= second_intersection && second_intersection > 0.0f))
        return std::optional<Hit_result>();
    
    const glm::vec3 normal = glm::normalize(-glm::sign(dir) * glm::step({sc.y, sc.z, sc.x}, sc) * 
                             glm::step({sc.z, sc.x, sc.y}, sc));
    const glm::vec3 hit_point = start + dir * first_intersection;
    const float lenght = first_intersection;

    return Hit_result(normal, hit_point, lenght);
}

float Collision_algorithms::project_point_to_axis(glm::vec3 point, glm::vec3 axis)
{
    axis = glm::normalize(axis);
    return glm::dot(point, axis);
}
