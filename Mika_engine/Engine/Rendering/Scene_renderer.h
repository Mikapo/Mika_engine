#pragma once

#include "Datatypes/Frame_data.h"
#include "OpenGL/Shading/Shader.h"
#include "OpenGL/Shading/Shadow_map.h"
#include "OpenGL_buffers.h"
#include <memory>

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
        // Should be called before use
        void initialize();

        // Should be called after not using anymore
        void cleanup() noexcept;

        [[nodiscard]] Render_settings get_render_settings() const noexcept;
        void set_render_settings(Render_settings settings) noexcept;

        void render_frame(Frame_data frame);
        void update_window_size(int32_t width, int32_t height) noexcept;

    private:
        void update_camera(const Camera_data& camera_data);
        void update_lighting(const std::vector<Light_data>& lighting);
        void update_settings();

        void draw_to_shadow_map(const std::vector<Mesh_data>& meshes);
        void draw_collisions(const std::vector<Transform>& collisions, OpenGL::Shader& shader);
        void draw_meshes(const std::vector<Mesh_data>& meshes, OpenGL::Shader& shader);
        void draw_mesh(
            const OpenGL::Buffers& buffers, Transform transform, const Material& material, OpenGL::Shader& shader);

        void apply_material(const Material& material, OpenGL::Shader& shader);

        OpenGL_buffers m_buffers;
        std::unique_ptr<OpenGL::Shader> m_scene_shader = nullptr;
        std::unique_ptr<OpenGL::Shadow_map> m_shadow_map = nullptr;

        bool m_has_been_initialized = false;
        int32_t m_window_width = 0, m_window_height = 0;
        float m_aspect_ratio = 0.0F;

        Render_settings m_render_settings;
    };

} // namespace MEngine
