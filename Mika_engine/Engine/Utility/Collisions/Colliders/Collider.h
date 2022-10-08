#pragma once

#include "Datatypes/Axis.h"
#include "Datatypes/Axis_comparison_result.h"
#include "Datatypes/Collision_result.h"
#include "Datatypes/Hit_result.h"
#include "Datatypes/Transform.h"
#include "glm/vec3.hpp"
#include <optional>

namespace MEngine
{
    struct Line;
    class Sphere;
    class Oriented_bounding_box;
    class Collider
    {
    public:
        virtual ~Collider() = default;

        glm::vec3 get_origin() const noexcept;
        glm::mat4 get_model() const noexcept;
        Axis_comparison_result compare_to_axis(glm::vec3 axis_origin, Axis axis) const noexcept;
        virtual void update(Transform transform);
        virtual std::optional<Collision_result> is_overlapping(const Collider* collider) const = 0;
        virtual std::optional<Hit_result> is_overlapping_with_line(const Line& line) const = 0;
        virtual std::optional<Collision_result> is_overlapping_with_obb(
            const Oriented_bounding_box& collider) const = 0;
        virtual std::optional<Collision_result> is_overlapping_with_sphere(const Sphere& collider) const = 0;

    protected:
        glm::vec3 m_extend = {0.0f, 0.0f, 0.0f};

    private:
        glm::vec3 m_origin = {0.0f, 0.0f, 0.0f};
        glm::mat4 m_model = glm::mat4(1.0f);
    };

} // namespace MEngine
