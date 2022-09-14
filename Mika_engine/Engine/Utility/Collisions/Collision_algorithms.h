#pragma once

#include "Datatypes/Collision_result.h"
#include "Datatypes/Hit_result.h"
#include "Datatypes/Min_max.h"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include <array>
#include <limits>
#include <optional>

namespace Mika_engine
{
    struct Line;
    class Oriented_bounding_box;
    class Sphere;
    class Collision_algorithms
    {
    public:
        Collision_algorithms() = delete;
        static std::optional<Collision_result> obb_and_obb(
            const Oriented_bounding_box& a, const Oriented_bounding_box& b);
        static std::optional<Collision_result> obb_and_sphere(const Oriented_bounding_box& obb, const Sphere& sphere);
        static std::optional<Collision_result> sphere_and_sphere(const Sphere& a, const Sphere& b);
        static std::optional<Hit_result> line_and_obb(const Line& line, const Oriented_bounding_box& box);
        static std::optional<Hit_result> line_and_sphere(const Line& line, const Sphere& sphere);
        static std::optional<Hit_result> ray_and_aabb(
            glm::vec3 start, glm::vec3 dir, glm::vec3 box_min, glm::vec3 box_max);
        static std::optional<Hit_result> ray_and_sphere(glm::vec3 start, glm::vec3 dir, const Sphere& sphere);

    private:
        static Hit_result apply_model_to_hit_result(Hit_result hit_result, glm::mat4 model);

        template <size_t vertice_amount>
        static Min_max get_min_max_from_axis_projection(
            const std::array<glm::vec3, vertice_amount>& points, glm::vec3 axis)
        {
            float min = std::numeric_limits<float>::infinity();
            float max = -std::numeric_limits<float>::infinity();

            for (const glm::vec3 point : points)
            {
                const float projection = project_point_to_axis(point, axis);

                if (projection < min)
                    min = projection;

                if (projection > max)
                    max = projection;
            }

            return {.m_min = min, .m_max = max};
        }

        template <size_t size>
        using vec3_array_ref = const std::array<glm::vec3, size>&;

        template <size_t a_vertice_amount, size_t b_vertice_amount, size_t axis_amount>
        static std::optional<Collision_result> sat_algorithm(
            vec3_array_ref<a_vertice_amount> a_vertices, vec3_array_ref<b_vertice_amount> b_vertices,
            vec3_array_ref<axis_amount> axises)
        {
            for (const glm::vec3 axis : axises)
            {
                const Min_max min_max = get_min_max_from_axis_projection(a_vertices, axis);
                const Min_max other_min_max = get_min_max_from_axis_projection(b_vertices, axis);

                if (min_max.m_min < other_min_max.m_min && min_max.m_max < other_min_max.m_min)
                    return std::optional<Collision_result>();

                if (min_max.m_min > other_min_max.m_max && min_max.m_max > other_min_max.m_max)
                    return std::optional<Collision_result>();
            }

            return std::optional<Collision_result>(Collision_result());
        }

        static float project_point_to_axis(glm::vec3 point, glm::vec3 axis);
    };

} // namespace Mika_engine
