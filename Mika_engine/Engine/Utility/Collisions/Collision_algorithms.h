#pragma once

#include <array>
#include <limits>
#include <optional>
#include "Datatypes/Min_max.h"
#include "Datatypes/Hit_result.h"
#include "glm/vec3.hpp"

struct Line;
class Oriented_bounding_box;
class Collision_algorithms
{
public:
    static bool obb_and_obb(const Oriented_bounding_box& a, const Oriented_bounding_box& b);
    static std::optional<Hit_result> line_and_obb(const Line& line, const Oriented_bounding_box& box);
    static std::optional<Hit_result> ray_and_aabb(glm::vec3 start, glm::vec3 dir, glm::vec3 box_min, glm::vec3 box_max);

private:
    Collision_algorithms() = default;

    template<size_t vertice_amount>
    static Min_max get_min_max_from_axis_projection(const std::array<glm::vec3, vertice_amount>& points, glm::vec3 axis)
    {
        float min = std::numeric_limits<float>::infinity();
        float max = -std::numeric_limits<float>::infinity();

        for (glm::vec3 point : points)
        {
            const float projection = project_point_to_axis(point, axis);

            if (projection < min)
                min = projection;

            if (projection > max)
                max = projection;
        }

        return {.m_min = min, .m_max = max};
    }

    template<size_t size>
    using vec3_array_ref = const std::array<glm::vec3, size>&;

    template<size_t a_vertice_amount, size_t b_vertice_amount, size_t axis_amount>
    static bool sat_algorithm(
        vec3_array_ref<a_vertice_amount> a_vertices, vec3_array_ref<b_vertice_amount> b_vertices,
        vec3_array_ref<axis_amount> axises)
    {
        for (glm::vec3 axis : axises)
        {
            const Min_max min_max = get_min_max_from_axis_projection(a_vertices, axis);
            const Min_max other_min_max = get_min_max_from_axis_projection(b_vertices, axis);

            if (min_max.m_min < other_min_max.m_min && min_max.m_max < other_min_max.m_min)
                return false;

            if (min_max.m_min > other_min_max.m_max && min_max.m_max > other_min_max.m_max)
                return false;
        }

        return true;
    }

    static float project_point_to_axis(glm::vec3 point, glm::vec3 axis);
};
