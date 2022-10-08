#pragma once

#include "Datatypes/Frame_data.h"
#include "OpenGL/Shading/Shader.h"
#include "OpenGL/Shading/Shadow_map.h"
#include "OpenGL_buffers.h"
#include <condition_variable>
#include <memory>
#include <queue>

namespace MEngine
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

    class Scene_renderer
    {
    public:
        void initialize();
        void cleanup() noexcept;
        void render_frame(Frame_data frame);
        Render_settings get_render_settings() const noexcept;
        void set_render_settings(Render_settings settings) noexcept;
        void update_window_size(int32_t width, int32_t height) noexcept;

    private:
        void update_camera(const Camera_data& camera_data);
        void update_lighting(const std::vector<Light_data>& lighting);
        void update_settings();
        void render_to_shadow_Map(std::vector<Mesh_data>& meshes);
        void draw_collisions(const std::vector<Transform>& collisions, OpenGL::Shader& shader);
        void draw_meshes(std::vector<Mesh_data>& meshes, OpenGL::Shader& shader);
        void draw_mesh(
            const OpenGL::Buffers& buffers, Transform transform, const Material& material, OpenGL::Shader& shader);
        void apply_material(const Material& material, OpenGL::Shader& shader);

        bool m_has_been_initialized = false;

        OpenGL_buffers m_buffers;
        std::unique_ptr<OpenGL::Shader> m_scene_shader;
        std::unique_ptr<OpenGL::Shadow_map> m_shadow_map;
        int32_t m_window_width, m_window_height;

        Render_settings m_render_settings;
    };

} // namespace MEngine
