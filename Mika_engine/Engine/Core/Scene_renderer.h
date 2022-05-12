#pragma once

#include "Rendering/Shading/Shader.h"
#include "Rendering/Shading/Shadow_map.h"
#include <queue>
#include <memory>
#include <condition_variable>
#include "Utility/Frame_data.h"

struct Render_settings
{
	bool ambient_enabled = true;
	bool diffuse_enabled = true;
	bool specular_enabled = true;
	bool shadow_enabled = true;
	bool texture_enabled = true;
};

class Mesh;
class Light_data;
class Camera_data;
class Render_frame;
class World;
class Scene_renderer
{
public:
	void cleanup();
	void render_frame();
	void add_mesh_to_render(const Mesh_data& mesh);
	void add_light_to_render(const Light_data& light);
	void add_camera_to_render(const Camera_data& camera);
	void set_render_settings(Render_settings settings);
	Render_settings get_render_settings() const;
	void end_frame();
	void update_window_size(int32_t width, int32_t height);
	size_t how_many_frames_behind();

private:
	void update_camera();
	void update_lighting();
	void update_settings();
	void render_to_shadow_Map();
	void draw_meshes(Shader* shader);
	void draw_mesh(Mesh_data& mesh, Shader* shader);
	void initialize();

	bool m_has_been_initialized = false;
	std::unique_ptr <Shader> m_scene_shader;
	Shadow_map m_shadow_map;
	int32_t m_window_width, m_window_height;
	std::queue<Frame_data> m_frames;
	std::condition_variable m_wait_until_has_frames;
	std::mutex m_wait_mutex;
	Render_settings m_render_settings;
};

