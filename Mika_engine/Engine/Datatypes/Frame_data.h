#pragma once

#include "Assets/Material.h"
#include "Assets/Mesh.h"
#include "Transform.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include <memory>

namespace MEngine
{
    class Light_data
    {
    public:
        Transform m_light_transform;
        glm::vec4 m_color = {0.0f, 0.0f, 0.0f, 1.0f};
    };

    class Camera_data
    {
    public:
        Transform m_camera_transform;
        float m_min_clip = 0.0f;
        float m_max_clip = 0.0f;
        float m_fov = 0.0f;
    };

    class Mesh_data
    {
    public:
        Transform m_transform;
        Mesh m_mesh;
        Material m_material;
    };

    class Frame_data
    {
    public:
        std::vector<Mesh_data> m_meshes;
        std::vector<Light_data> m_lighting;
        Camera_data m_camera;
        std::vector<Transform> m_box_collisions;
    };
} // namespace MEngine
