#pragma once

#include "Datatypes/Axis.h"
#include "Datatypes/Axis_comparison_result.h"
#include "glm/vec3.hpp"

namespace MEngine
{
    struct Line
    {
        glm::vec3 m_start;
        glm::vec3 m_end;

        glm::vec3 get_direction() const;
        float get_lenght() const;
        Axis_comparison_result compare_to_axis(glm::vec3 axis_origin, Axis axis) const;
    };
} // namespace MEngine
