#pragma once

#include "Rendering/Shading/Shader.h"
#include "Rendering/Shading/Shadow_map.h"
#include <queue>
#include <memory>
#include <condition_variable>
#include "Datatypes/Frame_data.h"

namespace Mika_engine
{
    struct Render_settings
    {
        bool ambient_enabled = true;
        bool diffuse_enabled = true;
        bool specular_enabled = true;
        bool shadow_enabled = true;
        bool texture_enabled = true;
        bool render_collisions = false;
    };

    class Engine;
    class Scene_renderer
    {
    public:
        void initialize();
        void cleanup() noexcept;
        void render_frame(Frame_data frame);
        Render_settings get_render_settings() const noexcept;
        void set_render_settings(Render_settings settings) noexcept;
        void new_frame(Frame_data in_frame);
        void update_window_size(int32_t width, int32_t height) noexcept;
        size_t frames_in_queue() noexcept;

    private:
        void update_camera(const Camera_data& camera_data);
        void update_lighting(const std::vector<Light_data>& lighting);
        void update_settings();
        void render_to_shadow_Map(std::vector<Mesh_data>& meshes);
        void draw_collisions(const std::vector<Transform>& collisions, OpenGL::Shader* shader);
        void draw_meshes(std::vector<Mesh_data>& meshes, OpenGL::Shader* shader);
        void draw_mesh(Mesh* mesh, Transform transform, Material& material, OpenGL::Shader* shader);

        bool m_has_been_initialized = false;

        std::unique_ptr<OpenGL::Shader> m_scene_shader;
        OpenGL::Shadow_map m_shadow_map;
        int32_t m_window_width, m_window_height;
     
        Render_settings m_render_settings;
        std::shared_ptr<Mesh> m_cube_mesh = nullptr;
    };

}
