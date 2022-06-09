#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <memory>
#include <unordered_map>

#include "Shader.h"
#include "Assets/Texture.h"
#include "Rendering/Texture/Texture_slots.h"

class Texture;
class Shader;
class Material
{
public:
	glm::vec4 m_ambient = { 0.1f, 0.1f, 0.1f, 1.0f };
	glm::vec4 m_diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	glm::vec4 m_specular = { 5.0f, 5.0f, 5.0f, 1.0f };
	float m_shininess = 200.0f;

	void add_texture(std::shared_ptr<Texture> texture, Texture_slot slot);
	void update_shader(Shader* shader) const;
	void bind_textures();
	void unbind_texture();
	
private:
	std::unordered_map<Texture_slot, std::shared_ptr<Texture>> m_textures;
};

