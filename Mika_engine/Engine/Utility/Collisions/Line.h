#pragma once

#include "glm/vec3.hpp"

struct Line
{
    glm::vec3 m_start;
    glm::vec3 m_end;

    glm::vec3 get_direction() const;
};
