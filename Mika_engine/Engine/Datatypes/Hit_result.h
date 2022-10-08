#pragma once

#include "glm/vec3.hpp"

namespace MEngine
{
    class Collision_component;
    struct Hit_result
    {
        glm::vec3 m_normal = {0.0f, 0.0f, 0.0f};
        glm::vec3 m_hit_point = {0.0f, 0.0f, 0.0f};
        float m_lenght = 0.0f;
        Collision_component* m_component;
    };
} // namespace MEngine
