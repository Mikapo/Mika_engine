#include "Collider.h"

#include "Datatypes/Min_max.h"
#include <stdexcept>

namespace Mika_engine
{
    glm::vec3 Collider::get_origin() const noexcept
    {
        return m_origin;
    }

    glm::mat4 Collider::get_model() const noexcept
    {
        return m_model;
    }

    Axis_comparison_result Collider::compare_to_axis(glm::vec3 axis_origin, Axis axis) const noexcept
    {
        const glm::vec3 origin = get_origin();
        float value_to_compare = 0.0f;
        Min_max box_min_max = {0.0f, 0.0f};

        switch (axis)
        {
        case Axis::x:
            value_to_compare = axis_origin.x;
            box_min_max = {.m_min = origin.x - m_extend.x, .m_max = origin.x + m_extend.x};
            break;
        case Axis::y:
            value_to_compare = axis_origin.y;
            box_min_max = {.m_min = origin.y - m_extend.y, .m_max = origin.y + m_extend.y};
            break;
        case Axis::z:
            value_to_compare = axis_origin.z;
            box_min_max = {.m_min = origin.z - m_extend.z, .m_max = origin.z + m_extend.z};
            break;
        }

        if (value_to_compare < box_min_max.m_min && value_to_compare < box_min_max.m_max)
            return Axis_comparison_result::right;
        else if (value_to_compare > box_min_max.m_min && value_to_compare > box_min_max.m_max)
            return Axis_comparison_result::left;
        else
            return Axis_comparison_result::overlap;
    }

    void Collider::update(Transform transform)
    {
        m_origin = transform.m_location;
        m_model = transform.calculate_model();
    }

} // namespace Mika_engine
