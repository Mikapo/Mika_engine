#pragma once

#include "glm/vec3.hpp"
#include "Datatypes/Axis_comparison_result.h"
#include "Datatypes/Axis.h"

namespace Mika_engine
{
    struct Line
    {
        glm::vec3 m_start;
        glm::vec3 m_end;

        glm::vec3 get_direction() const;
        float get_lenght() const;
        Axis_comparison_result compare_to_axis(glm::vec3 axis_origin, Axis axis) const;
    };
}

