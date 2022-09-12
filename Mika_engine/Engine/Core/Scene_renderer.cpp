#include "Scene_renderer.h"
#include "Core/Mika_engine.h"
#include "Objects/World.h"
#include "Utility/Uniform_names.h"
#include "gsl/gsl"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Rendering/Shading/Shaders.h"
#include "Rendering/Renderer.h"

void Scene_renderer::initialize(Mika_engine* engine)
{
    if (!engine)
        throw std::invalid_argument("engine was null");
    
    m_scene_shader = OpenGL::Shaders::compile_shader_from_file("Engine/Shaders/Lighting.vert", "Engine/Shaders/Lighting.frag");

    std::unique_ptr shadow_shader =
        OpenGL::Shaders::compile_shader_from_file("Engine/Shaders/Shadow_map.vert", "Engine/Shaders/Shadow_map.frag");

    m_shadow_map.init(std::move(shadow_shader));

    m_cube_mesh = engine->get_asset_manager().get_mesh("Engine/Engine_models/cube.obj");

    m_has_been_initialized = true;
}

void Scene_renderer::update_camera()
{
    const auto& frame = m_frames.front();
    const auto& camera_data = frame.m_camera;

    const glm::mat4 camera_rotation = camera_data.m_camera_transform.m_rotation.calculate_rotation_matrix();
    glm::vec3 camera_location = camera_data.m_camera_transform.m_location;
    camera_location.z *= -1;
    const glm::vec3 camera_forward = {camera_rotation[0][0], camera_rotation[0][1], camera_rotation[0][2]};
    const glm::vec3 camera_up = {camera_rotation[2][0], camera_rotation[2][1], camera_rotation[2][2]};

    float aspect_ratio = 0.0f;
    if (m_window_width > 1.0f && m_window_height > 1.0f)
        aspect_ratio = static_cast<float>(m_window_width) / static_cast<float>(m_window_height);

    const glm::mat4 look_at = glm::lookAt(camera_location, camera_location + camera_forward, -camera_up);
    const glm::mat4 projection =
        glm::perspective(glm::radians(camera_data.m_fov), aspect_ratio, camera_data.m_min_clip, camera_data.m_max_clip);

    m_scene_shader->set_uniform(Uniform_names::projection, projection);
    m_scene_shader->set_uniform(Uniform_names::view, look_at);
    m_scene_shader->set_uniform(Uniform_names::eye_location, camera_location.x, camera_location.y, camera_location.z);
}

void Scene_renderer::update_lighting()
{
    const auto& frame = m_frames.front();

    if (frame.m_lighting.size() == 0)
        return;

    const Light_data& light_data = frame.m_lighting.at(0);
    glm::vec3 light_pos = light_data.m_light_transform.m_location;
    light_pos.z *= -1.0f;

    constexpr float near_plane = 1.0f, far_plane = 1000.0f;
    constexpr float ortho_size = 10.0f;
    const glm::mat4 light_projection =
        glm::ortho(-ortho_size, ortho_size, -ortho_size, ortho_size, near_plane, far_plane);
    const glm::mat4 light_view = glm::lookAt(light_pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::mat4 light_space = light_projection * light_view;

    m_scene_shader->set_uniform(Uniform_names::light_location, light_pos.x, light_pos.y, light_pos.z);
    m_scene_shader->set_uniform(
        Uniform_names::light_color, light_data.m_color.r, light_data.m_color.g, light_data.m_color.b,
        light_data.m_color.a);
    m_scene_shader->set_uniform(Uniform_names::light_space, light_space);
    m_shadow_map.get_shader()->set_uniform(Uniform_names::light_space, light_space);
}

void Scene_renderer::update_settings()
{
    m_scene_shader->set_uniform(Uniform_names::ambient_enabled, m_render_settings.ambient_enabled);
    m_scene_shader->set_uniform(Uniform_names::diffuse_enabled, m_render_settings.diffuse_enabled);
    m_scene_shader->set_uniform(Uniform_names::specular_enabled, m_render_settings.specular_enabled);
    m_scene_shader->set_uniform(Uniform_names::shadow_enabled, m_render_settings.shadow_enabled);
    m_scene_shader->set_uniform(Uniform_names::texture_enabled, m_render_settings.texture_enabled);
}

void Scene_renderer::render_to_shadow_Map()
{
    OpenGL::Renderer::start_drawing_to_shadow_map(m_shadow_map);
    draw_meshes(m_shadow_map.get_shader());
    OpenGL::Renderer::stop_drawing_to_shadow_map(m_shadow_map, m_window_width, m_window_height);
    m_shadow_map.bind_depth_map();
}

void Scene_renderer::draw_collisions(OpenGL::Shader* shader)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Material material;

    auto& collisions = m_frames.front().m_box_collisions;

    for (Transform collision : collisions)
        draw_mesh(m_cube_mesh.get(), collision, material, shader);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Scene_renderer::draw_meshes(OpenGL::Shader* shader)
{
    std::vector<Mesh_data>& meshes = m_frames.front().m_meshes;

    for (Mesh_data& mesh_data : meshes)
        draw_mesh(mesh_data.m_mesh.get(), mesh_data.m_transform, mesh_data.m_material, shader);
}

void Scene_renderer::draw_mesh(Mesh* mesh, Transform transform, Material& material, OpenGL::Shader* shader)
{
    if (!mesh)
        throw std::invalid_argument("mesh was null");

    if (!shader)
        throw std::invalid_argument("shader was null");

    material.update_shader(shader);
    material.bind_textures();

    transform.m_rotation.m_roll -= 90.0f;
    transform.m_location.z *= -1.0f;

    const glm::vec3 scale = transform.m_scale;
    transform.m_scale.z = scale.y;
    transform.m_scale.y = scale.z;

    const glm::mat4 model = transform.calculate_model();

    shader->set_uniform(Uniform_names::model, model);
    
    OpenGL::Renderer::draw(*mesh->get_buffers(), *shader);

    material.unbind_texture();
}

void Scene_renderer::cleanup() noexcept
{
    m_scene_shader.reset();

    while (!m_frames.empty())
        m_frames.pop();

    m_has_been_initialized = false;
}

void Scene_renderer::render_frame()
{
    if (!m_has_been_initialized)
        return;

    if (frames_in_queue() == 0)
        return;

    std::unique_lock lock(m_wait_mutex);
    auto wait_lambda = [this]() noexcept { return frames_in_queue() > 2; };
    m_wait_until_has_frames.wait(lock, wait_lambda);

    update_settings();
    update_camera();
    update_lighting();

    if (m_render_settings.shadow_enabled)
        render_to_shadow_Map();

    draw_meshes(m_scene_shader.get());

    if (m_render_settings.render_collisions)
        draw_collisions(m_scene_shader.get());

    m_frames.pop();
}

void Scene_renderer::set_render_settings(Render_settings settings) noexcept
{
    m_render_settings = settings;
}

Render_settings Scene_renderer::get_render_settings() const noexcept
{
    return m_render_settings;
}

void Scene_renderer::new_frame(Frame_data in_frame)
{
    m_frames.emplace(std::move(in_frame));
    m_wait_until_has_frames.notify_one();
}

void Scene_renderer::update_window_size(int32_t width, int32_t height) noexcept
{
    m_window_width = width;
    m_window_height = height;
}

size_t Scene_renderer::frames_in_queue() noexcept
{
    return m_frames.size();
}
