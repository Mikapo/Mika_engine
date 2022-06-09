#include "Scene_renderer.h"
#include "Objects/World.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Utility/Uniform_names.h"
#include "Core/Mika_engine.h"

void Scene_renderer::initialize(Mika_engine* engine)
{
	m_scene_shader = std::make_unique<Shader>("Engine/Shaders/Lighting.frag", "Engine/Shaders/Lighting.vert");

	const int32_t shadow_width = 1500, shadows_height = 1500;
	m_shadow_map.init(shadow_width, shadows_height);

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
	const glm::vec3 camera_forward = { camera_rotation[0][0], camera_rotation[0][1], camera_rotation[0][2] };
	const glm::vec3 camera_up = { camera_rotation[2][0], camera_rotation[2][1], camera_rotation[2][2] };

	float aspect_ratio = 0.0f;
	if (m_window_width > 1.0f && m_window_height > 1.0f)
		aspect_ratio = static_cast<float>(m_window_width) / static_cast<float>(m_window_height);

	const glm::mat4 look_at = glm::lookAt(camera_location, camera_location + camera_forward, -camera_up);
	const glm::mat4 projection = glm::perspective(glm::radians(camera_data.m_fov), aspect_ratio, camera_data.m_min_clip, camera_data.m_max_clip);

	m_scene_shader->set_uniform_mat4f(Uniform_names::projection, projection);
	m_scene_shader->set_uniform_mat4f(Uniform_names::view, look_at);
	m_scene_shader->set_uniform3f(Uniform_names::eye_location, camera_location.x, camera_location.y, camera_location.z);
}

void Scene_renderer::update_lighting()
{
	const auto& frame = m_frames.front();

	if (frame.m_lighting.size() == 0)
		return;

	const Light_data& light_data = frame.m_lighting[0];
	glm::vec3 light_pos = light_data.m_light_transform.m_location;
	light_pos.z *= -1.0f;

	const float near_plane = 1.0f, far_plane = 1000.0f;
	const float ortho_size = 10.0f;
	const glm::mat4 light_projection = glm::ortho(-ortho_size, ortho_size, -ortho_size, ortho_size, near_plane, far_plane);
	const glm::mat4 light_view = glm::lookAt(light_pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	const glm::mat4 light_space = light_projection * light_view;

	m_scene_shader->set_uniform3f(Uniform_names::light_location, light_pos.x, light_pos.y, light_pos.z);
	m_scene_shader->set_uniform4f(Uniform_names::light_color, light_data.m_color.r, light_data.m_color.g, light_data.m_color.b, light_data.m_color.a);
	m_scene_shader->set_uniform_mat4f(Uniform_names::light_space, light_space);
	m_shadow_map.update_shader(light_space);
}

void Scene_renderer::update_settings()
{
	m_scene_shader->set_uniform1i(Uniform_names::ambient_enabled, m_render_settings.ambient_enabled);
	m_scene_shader->set_uniform1i(Uniform_names::diffuse_enabled, m_render_settings.diffuse_enabled);
	m_scene_shader->set_uniform1i(Uniform_names::specular_enabled, m_render_settings.specular_enabled);
	m_scene_shader->set_uniform1i(Uniform_names::shadow_enabled, m_render_settings.shadow_enabled);
	m_scene_shader->set_uniform1i(Uniform_names::texture_enabled, m_render_settings.texture_enabled);
}

void Scene_renderer::render_to_shadow_Map()
{
	int32_t shadow_width = 0, shadow_height = 0;
	m_shadow_map.get_shadow_resolution(shadow_width, shadow_height);
	m_shadow_map.bind_frame_buffer();
	glViewport(0, 0, shadow_width, shadow_height);
	glCullFace(GL_FRONT);
	glClear(GL_DEPTH_BUFFER_BIT);
	draw_meshes(m_shadow_map.get_shader());
	glCullFace(GL_BACK);
	m_shadow_map.unbind_frame_buffer();
    glViewport(0, 0, static_cast<GLsizei>(m_window_width), static_cast<GLsizei>(m_window_height));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shadow_map.bind_texture(Texture_slot::shadow_map);
}

void Scene_renderer::draw_collisions(Shader* shader)
{ 
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	Material material;

    for (auto& collision_box : m_frames.front().m_box_collisions)
        draw_mesh(m_cube_mesh, collision_box, material, shader);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Scene_renderer::draw_meshes(Shader* shader)
{
	for (auto& mesh_data : m_frames.front().m_meshes)
        draw_mesh(mesh_data.m_mesh, mesh_data.m_transform, mesh_data.m_material, shader);
}

void Scene_renderer::draw_mesh(std::shared_ptr<Mesh> mesh, Transform transform, Material& material, Shader* shader)
{
    material.update_shader(shader);
    material.bind_textures();
    mesh->bind_buffers();

	transform.m_rotation.m_roll -= 90.0f;
    transform.m_location.z *= -1.0f;

	glm::vec3 scale = transform.m_scale;
    transform.m_scale.z = scale.y;
    transform.m_scale.y = scale.z;

	const glm::mat4 model = transform.calculate_model();

	shader->set_uniform_mat4f(Uniform_names::model, model);
	shader->bind();

	const GLsizei indices_count = static_cast<GLsizei>(mesh->get_indices_count());
    glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, nullptr);

	material.unbind_texture();
	shader->unbind();
    mesh->unbind_buffers();
}

void Scene_renderer::cleanup()
{
	m_scene_shader.reset();
	m_shadow_map.cleanup();
	
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
    m_wait_until_has_frames.wait(lock, [this] { return frames_in_queue() > 2; });

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

void Scene_renderer::add_mesh_to_render(const Mesh_data& mesh)
{
    if (m_frames.empty())
        new_frame();

	auto& frame = m_frames.back();
	frame.m_meshes.emplace_back(mesh);
}

void Scene_renderer::add_light_to_render(const Light_data& light)
{
    if (m_frames.empty())
        new_frame();

	auto& frame = m_frames.back();
	frame.m_lighting.emplace_back(light);
}

void Scene_renderer::add_camera_to_render(const Camera_data& camera)
{
    if (m_frames.empty())
        new_frame();

	auto& frame = m_frames.back();
	frame.m_camera = camera;
}

void Scene_renderer::add_collision_box_to_render(const Transform& box_transform) 
{
    if (m_frames.empty())
        new_frame();

    m_frames.back().m_box_collisions.push_back(box_transform);
}

void Scene_renderer::set_render_settings(Render_settings settings)
{
	m_render_settings = settings;
}

Render_settings Scene_renderer::get_render_settings() const
{
	return m_render_settings;
}

void Scene_renderer::new_frame()
{
	m_frames.emplace(Frame_data());
	m_wait_until_has_frames.notify_one();
}

void Scene_renderer::update_window_size(int32_t width, int32_t height)
{
	m_window_width = width;
	m_window_height = height;
}

size_t Scene_renderer::frames_in_queue() 
{
	return m_frames.size();
}
