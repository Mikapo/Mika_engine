#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <memory>
#include <unordered_map>

#include "Rendering/Shading/Shader.h"
#include "Rendering/Texture/Texture.h"
#include "Rendering/Texture/Texture_slots.h"

class Texture;
class Shader;
class Material
{
public:
	glm::vec4 m_ambient = { 0.1f, 0.1f, 0.1f, 1.0f };
	glm::vec4 m_diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	glm::vec4 m_specular = { 5.0f, 5.0f, 5.0f, 1.0f };
    glm::vec4 m_default_color = {0.6f, 0.6f, 0.6f, 1.0f};
	float m_shininess = 200.0f;

	void add_texture(std::shared_ptr<OpenGL::Texture> texture);
    void remove_texture(OpenGL::Texture_slot slot) noexcept;
    void update_shader(OpenGL::Shader* shader) const;
	void bind_textures() noexcept;
    void unbind_texture() noexcept;
	
private:
	std::unordered_map<OpenGL::Texture_slot, std::shared_ptr<OpenGL::Texture>> m_textures;
};

