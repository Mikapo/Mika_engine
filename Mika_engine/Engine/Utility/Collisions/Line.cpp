#include "Line.h"
#include "glm/geometric.hpp"
#include <stdexcept>

namespace MEngine
{
    glm::vec3 Line::get_direction() const
    {
        return glm::normalize(m_end - m_start);
    }

    float Line::get_lenght() const
    {
        return glm::length(m_end - m_start);
    }

    Axis_comparison_result Line::compare_to_axis(glm::vec3 axis_origin, Axis axis) const
    {
        switch (axis)
        {
        case Axis::x:
            if (m_start.x > axis_origin.x && m_end.x > axis_origin.x)
                return Axis_comparison_result::right;
            else if (m_start.x < axis_origin.x && m_end.x < axis_origin.x)
                return Axis_comparison_result::left;
            else
                return Axis_comparison_result::overlap;
        case Axis::y:
            if (m_start.y > axis_origin.y && m_end.y > axis_origin.y)
                return Axis_comparison_result::right;
            else if (m_start.y < axis_origin.y && m_end.y < axis_origin.y)
                return Axis_comparison_result::left;
            else
                return Axis_comparison_result::overlap;
        case Axis::z:
            if (m_start.z > axis_origin.z && m_end.z > axis_origin.z)
                return Axis_comparison_result::right;
            else if (m_start.z < axis_origin.z && m_end.z < axis_origin.z)
                return Axis_comparison_result::left;
            else
                return Axis_comparison_result::overlap;
        default:
            throw std::invalid_argument("invalid enum");
        }
    }
} // namespace MEngine
