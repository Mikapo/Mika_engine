#pragma once

#include "glm/vec3.hpp"

namespace MEngine
{
    class Collision_component;
    struct Collision_result
    {
        Collision_component* m_this_component = nullptr;
        Collision_component* m_other_component = nullptr;
        glm::vec3 m_to_leave_collision = {0.0f, 0.0f, 0.0f};
    };
} // namespace MEngine
