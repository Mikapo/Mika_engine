#pragma once

#include <glm/mat4x4.hpp>
#include <memory>

#include "Rendering/Texture/Texture_slots.h"
#include "Rendering/Buffers/Buffers.h"

class Light;
class Shader;
class Shadow_map
{
public:
	Shadow_map() {}
	~Shadow_map();

	void cleanup();

	Shadow_map(const Shadow_map&) = delete;
	Shadow_map(const Shadow_map&&) = delete;
	void operator=(const Shadow_map&) = delete;
	void operator=(const Shadow_map&&) = delete;

	void init(int32_t shadow_width, int32_t shadow_height);
	void bind_frame_buffer() const;
	static void unbind_frame_buffer();
	void bind_texture(Texture_slot slot) const;
	static void unbind_texture();
	Shader* get_shader() const { return m_shader.get(); }
	void get_shadow_resolution(int32_t& out_width, int32_t& out_height) const;
	void update_shader(glm::mat4 light_space);

private:
	static uint32_t create_depth_map_texture(int32_t shadow_width, int32_t shadow_height);
	static uint32_t create_frame_buffer(uint32_t depth_map);

	bool m_has_been_initialized = false;
	int32_t m_shadow_width = 0, m_shadow_height = 0;
	std::unique_ptr<Shader> m_shader = nullptr;
	uint32_t m_frame_buffer = 0;
	uint32_t m_depth_map = 0;
};