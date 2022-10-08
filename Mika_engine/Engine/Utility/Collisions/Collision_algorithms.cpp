#include "Collision_algorithms.h"

#include "Colliders/Oriented_bounding_box.h"
#include "Colliders/Sphere.h"
#include "Debug/Debug_logger.h"
#include "Line.h"

namespace MEngine
{
    std::optional<Collision_result> Collision_algorithms::obb_and_obb(
        const Oriented_bounding_box& a, const Oriented_bounding_box& b)
    {
        const auto& a_normals = a.get_normals();
        const auto& b_normals = b.get_normals();

        const std::array<glm::vec3, 15> axises{
            a_normals.at(0),
            a_normals.at(1),
            a_normals.at(2),
            b_normals.at(0),
            b_normals.at(1),
            b_normals.at(2),
            glm::cross(a_normals.at(0), b_normals.at(0)),
            glm::cross(a_normals.at(0), b_normals.at(1)),
            glm::cross(a_normals.at(0), b_normals.at(2)),
            glm::cross(a_normals.at(1), b_normals.at(0)),
            glm::cross(a_normals.at(1), b_normals.at(1)),
            glm::cross(a_normals.at(1), b_normals.at(2)),
            glm::cross(a_normals.at(2), b_normals.at(0)),
            glm::cross(a_normals.at(2), b_normals.at(1)),
            glm::cross(a_normals.at(2), b_normals.at(2)),
        };

        return sat_algorithm(a.get_vertices(), b.get_vertices(), axises);
    }

    std::optional<Collision_result> Collision_algorithms::obb_and_sphere(
        const Oriented_bounding_box& obb, const Sphere& sphere)
    {
        const Transform obb_trasnform = obb.get_transform();
        const glm::mat4 model = obb_trasnform.calculate_translate_matrix() * obb_trasnform.calculate_rotation_matrix();
        const glm::mat4 inverse = glm::inverse(model);
        const glm::vec3 sphere_local_origin = inverse * glm::vec4(sphere.get_origin(), 1.0f);

        const glm::vec3 obb_local_max = obb_trasnform.m_location + obb_trasnform.m_scale;
        const glm::vec3 obb_local_min = obb_trasnform.m_location - obb_trasnform.m_scale;
        const glm::vec3 closest_point = glm::max(obb_local_min, glm::min(sphere_local_origin, obb_local_max));

        const glm::vec3 offset = closest_point - sphere_local_origin;

        if (glm::length(offset) <= sphere.get_radius())
        {
            Collision_result result;
            return result;
        }

        return std::optional<Collision_result>();
    }

    std::optional<Collision_result> Collision_algorithms::sphere_and_sphere(const Sphere& a, const Sphere& b)
    {
        const float distance = glm::length(a.get_origin() - b.get_origin());
        const float radius_sum = a.get_radius() + b.get_radius();

        if (distance <= radius_sum)
        {
            Collision_result result;
            return result;
        }
        else
            return std::optional<Collision_result>();
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
            hit_result = apply_model_to_hit_result(hit_result.value(), model);

            float& lenght = hit_result.value().m_lenght;
            lenght = glm::length(hit_result.value().m_hit_point - line.m_start);

            if (lenght > line.get_lenght())
                return std::optional<Hit_result>();
        }

        return hit_result;
    }

    std::optional<Hit_result> Collision_algorithms::line_and_sphere(const Line& line, const Sphere& sphere)
    {
        const glm::vec3 dir = glm::normalize(line.m_end - line.m_start);
        std::optional<Hit_result> hit_result = ray_and_sphere(line.m_start, dir, sphere);

        if (hit_result.has_value())
        {
            float& lenght = hit_result.value().m_lenght;
            lenght = glm::length(hit_result.value().m_hit_point - line.m_start);

            if (lenght > line.get_lenght())
                return std::optional<Hit_result>();
        }

        return std::optional<Hit_result>();
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

        const glm::vec3 normal =
            glm::normalize(-glm::sign(dir) * glm::step({sc.y, sc.z, sc.x}, sc) * glm::step({sc.z, sc.x, sc.y}, sc));
        const glm::vec3 hit_point = start + dir * first_intersection;

        return Hit_result(normal, hit_point);
    }

    std::optional<Hit_result> Collision_algorithms::ray_and_sphere(glm::vec3 start, glm::vec3 dir, const Sphere& sphere)
    {
        const glm::vec3 sphere_origin = sphere.get_origin();
        const float origin_projection_to_ray = glm::dot(sphere_origin - start, dir);
        const glm::vec3 closest_point_in_ray = start + dir * origin_projection_to_ray;
        const float distance_to_ray = glm::length(closest_point_in_ray - sphere_origin);
        const float radius = sphere.get_radius();
        const float distance_to_intersection = glm::sqrt(glm::pow(radius, 2.0f) + glm::pow(distance_to_ray, 2.0f));
        const float first_intersection = origin_projection_to_ray - distance_to_intersection;
        const float second_intersection = origin_projection_to_ray + distance_to_intersection;

        if (!(first_intersection <= second_intersection && second_intersection > 0.0f))
            return std::optional<Hit_result>();

        const glm::vec3 hit_point = start + dir * first_intersection;
        const glm::vec3 normal = glm::normalize(hit_point - sphere_origin);

        return Hit_result(normal, hit_point);
    }

    Hit_result Collision_algorithms::apply_model_to_hit_result(Hit_result hit_result, glm::mat4 model)
    {
        const glm::mat4 transpose = glm::transpose(glm::inverse(model));
        hit_result.m_normal = transpose * glm::vec4(hit_result.m_normal, 1.0f);
        hit_result.m_normal = glm::normalize(hit_result.m_normal);
        hit_result.m_hit_point = model * glm::vec4(hit_result.m_hit_point, 1.0f);
        return hit_result;
    }

    float Collision_algorithms::project_point_to_axis(glm::vec3 point, glm::vec3 axis)
    {
        axis = glm::normalize(axis);
        return glm::dot(point, axis);
    }

} // namespace MEngine
