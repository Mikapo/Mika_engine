#include "Scene_renderer.h"
#include "GL/glew.h"
#include "OpenGL/Renderer.h"
#include "OpenGL/Shading/Shaders.h"
#include "Utility/Uniform_names.h"
#include "gsl/gsl"
#include <glm/ext/matrix_transform.hpp>

namespace MEngine
{
    void Scene_renderer::initialize()
    {
        m_scene_shader =
            OpenGL::Shaders::compile_shader_from_file("Engine/Shaders/Lighting.vert", "Engine/Shaders/Lighting.frag");

        std::unique_ptr shadow_shader = OpenGL::Shaders::compile_shader_from_file(
            "Engine/Shaders/Shadow_map.vert", "Engine/Shaders/Shadow_map.frag");

        m_shadow_map = std::make_unique<OpenGL::Shadow_map>();
        m_shadow_map->init(std::move(shadow_shader));

        m_has_been_initialized = true;
    }

    void Scene_renderer::update_camera(const Camera_data& camera_data)
    {
        const Directional_vectors camera_directions =
            camera_data.m_camera_transform.m_rotation.calculate_directional_vectors();

        glm::vec3 camera_location = camera_data.m_camera_transform.m_location;
        camera_location.z *= -1;

        const glm::mat4 look_at =
            glm::lookAt(camera_location, camera_location + camera_directions.m_forward, -camera_directions.m_up);

        const glm::mat4 projection = glm::perspective(
            glm::radians(camera_data.m_fov), m_aspect_ratio, camera_data.m_min_clip, camera_data.m_max_clip);

        m_scene_shader->set_uniform(Uniform_names::projection, projection);
        m_scene_shader->set_uniform(Uniform_names::view, look_at);
        m_scene_shader->set_uniform(
            Uniform_names::eye_location, camera_location.x, camera_location.y, camera_location.z);
    }

    void Scene_renderer::update_lighting(const std::vector<Light_data>& lighting)
    {
        if (lighting.empty())
            return;

        const Light_data& light_data = lighting.at(0);
        glm::vec3 light_pos = light_data.m_light_transform.m_location;
        light_pos.z *= -1.0F;

        constexpr float near_plane = 1.0F, far_plane = 1000.0F;
        constexpr float ortho_size = 10.0F;
        const glm::mat4 light_projection =
            glm::ortho(-ortho_size, ortho_size, -ortho_size, ortho_size, near_plane, far_plane);

        const glm::mat4 light_view = glm::lookAt(light_pos, glm::vec3(0.0F, 0.0F, 0.0F), glm::vec3(0.0F, 1.0F, 0.0F));

        const glm::mat4 light_space = light_projection * light_view;

        m_scene_shader->set_uniform(Uniform_names::light_location, light_pos.x, light_pos.y, light_pos.z);
        m_scene_shader->set_uniform(
            Uniform_names::light_color, light_data.m_color.r, light_data.m_color.g, light_data.m_color.b,
            light_data.m_color.a);
        m_scene_shader->set_uniform(Uniform_names::light_space, light_space);
        m_shadow_map->get_shader()->set_uniform(Uniform_names::light_space, light_space);
    }

    void Scene_renderer::update_settings()
    {
        m_scene_shader->set_uniform(Uniform_names::ambient_enabled, m_render_settings.ambient_enabled);
        m_scene_shader->set_uniform(Uniform_names::diffuse_enabled, m_render_settings.diffuse_enabled);
        m_scene_shader->set_uniform(Uniform_names::specular_enabled, m_render_settings.specular_enabled);
        m_scene_shader->set_uniform(Uniform_names::shadow_enabled, m_render_settings.shadow_enabled);
        m_scene_shader->set_uniform(Uniform_names::texture_enabled, m_render_settings.texture_enabled);
    }

    void Scene_renderer::draw_to_shadow_map(const std::vector<Mesh_data>& meshes)
    {
        OpenGL::Renderer::start_drawing_to_shadow_map(*m_shadow_map);
        draw_meshes(meshes, *m_shadow_map->get_shader());
        OpenGL::Renderer::stop_drawing_to_shadow_map(*m_shadow_map, m_window_width, m_window_height);
        m_shadow_map->bind_depth_map();
    }

    void Scene_renderer::draw_collisions(const std::vector<Transform>& collisions, OpenGL::Shader& shader)
    {
        /* todo fix
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        Material material;


        for (Transform collision : collisions)
            draw_mesh(m_cube_mesh.get(), collision, material, shader);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        */
    }

    void Scene_renderer::draw_meshes(const std::vector<Mesh_data>& meshes, OpenGL::Shader& shader)
    {
        for (const Mesh_data& mesh_data : meshes)
        {
            const std::string mesh_location = mesh_data.m_mesh.get_mesh_location().data();
            const OpenGL::Buffers* buffers = m_buffers.get_object_buffers(mesh_location);

            if (buffers != nullptr)
                draw_mesh(*buffers, mesh_data.m_transform, mesh_data.m_material, shader);
        }
    }

    void Scene_renderer::draw_mesh(
        const OpenGL::Buffers& buffers, Transform transform, const Material& material, OpenGL::Shader& shader)
    {
        apply_material(material, shader);

        transform.m_rotation.m_roll -= 90.0F;
        transform.m_location.z *= -1.0F;

        const glm::vec3 scale = transform.m_scale;
        transform.m_scale.z = scale.y;
        transform.m_scale.y = scale.z;

        const glm::mat4 model = transform.calculate_model();

        shader.set_uniform(Uniform_names::model, model);
        OpenGL::Renderer::draw(buffers, shader);
    }

    void Scene_renderer::apply_material(const Material& material, OpenGL::Shader& shader)
    {
        shader.set_uniform(Uniform_names::ambient, material.m_ambient);
        shader.set_uniform(Uniform_names::diffuse, material.m_diffuse);
        shader.set_uniform(Uniform_names::specular, material.m_specular);
        shader.set_uniform(Uniform_names::shininess, material.m_shininess);
        shader.set_uniform(Uniform_names::default_color, material.m_default_color);
        shader.set_sampler_uniform(Uniform_names::shadow_map, OpenGL::Texture_slot::depth_map);
        shader.set_sampler_uniform(Uniform_names::texture, OpenGL::Texture_slot::color);

        const bool has_texture = material.get_textures().contains(OpenGL::Texture_slot::color);
        shader.set_uniform(Uniform_names::has_texture, static_cast<int32_t>(has_texture));

        for (const auto& texture : material.get_textures())
        {
            const std::string& texture_path = texture.second.texture_location;
            OpenGL::Texture* texture_buffer = m_buffers.get_texture(texture_path);

            if (texture_buffer != nullptr)
            {
                texture_buffer->set_slot(texture.first);
                texture_buffer->bind();
            }
        }
    }

    void Scene_renderer::cleanup() noexcept
    {
        m_scene_shader.reset();
        m_shadow_map.reset();
        m_buffers.clear();
        m_has_been_initialized = false;
    }

    void Scene_renderer::render_frame(Frame_data frame)
    {
        if (!m_has_been_initialized)
            return;

        update_settings();
        update_camera(frame.m_camera);
        update_lighting(frame.m_lighting);

        if (m_render_settings.shadow_enabled)
            draw_to_shadow_map(frame.m_meshes);

        draw_meshes(frame.m_meshes, *m_scene_shader);

        if (m_render_settings.render_collisions)
            draw_collisions(frame.m_box_collisions, *m_scene_shader);
    }

    void Scene_renderer::set_render_settings(Render_settings settings) noexcept
    {
        m_render_settings = settings;
    }

    Render_settings Scene_renderer::get_render_settings() const noexcept
    {
        return m_render_settings;
    }

    void Scene_renderer::update_window_size(int32_t width, int32_t height) noexcept
    {
        m_window_width = std::max(0, width);
        m_window_height = std::max(0, height);

        if (m_window_height != 0)
            m_aspect_ratio = static_cast<float>(m_window_width) / static_cast<float>(m_window_height);
        else
            m_aspect_ratio = 0;
    }
} // namespace MEngine
