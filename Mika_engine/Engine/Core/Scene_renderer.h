#pragma once

#include "Rendering/Shading/Shader.h"
#include "Rendering/Shading/Shadow_map.h"
#include <queue>
#include <memory>
#include <condition_variable>
#include "Datatypes/Frame_data.h"

struct Render_settings
{
	bool ambient_enabled = true;
	bool diffuse_enabled = true;
	bool specular_enabled = true;
	bool shadow_enabled = true;
	bool texture_enabled = true;
    bool render_collisions = false;
};

class Mika_engine;
class Scene_renderer
{
public:
    void initialize(Mika_engine* engine);
    void cleanup() noexcept;
	void render_frame();
    Render_settings get_render_settings() const noexcept;
    void set_render_settings(Render_settings settings) noexcept;
	void new_frame(Frame_data&& in_frame);
    void update_window_size(int32_t width, int32_t height) noexcept;
    size_t frames_in_queue() noexcept;

private:
	void update_camera();
	void update_lighting();
	void update_settings();
	void render_to_shadow_Map();
    void draw_collisions(Shader* shader);
	void draw_meshes(Shader* shader);
    void draw_mesh(const Mesh* mesh, Transform transform, Material& material, Shader* shader);

	bool m_has_been_initialized = false;
	std::unique_ptr <Shader> m_scene_shader;
	Shadow_map m_shadow_map;
	int32_t m_window_width, m_window_height;
	std::queue<Frame_data> m_frames;
	std::condition_variable m_wait_until_has_frames;
	std::mutex m_wait_mutex;
	Render_settings m_render_settings;
    std::shared_ptr<Mesh> m_cube_mesh = nullptr;
};

