#include "Material.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "Utility/Uniform_names.h"


void Material::add_texture(std::shared_ptr<Texture> texture, Texture_slot slot)
{
    m_textures[slot] = texture;
}

void Material::update_shader(Shader* shader) const
{
	shader->set_uniform4f(Uniform_names::ambient, m_ambient.x, m_ambient.y, m_ambient.z, m_ambient.w);
	shader->set_uniform4f(Uniform_names::diffuse, m_diffuse.x, m_diffuse.y, m_diffuse.z, m_diffuse.w);
	shader->set_uniform4f(Uniform_names::specular, m_specular.x, m_specular.y, m_specular.z, m_specular.w);
	shader->set_uniform1f(Uniform_names::shininess, m_shininess);

	shader->set_uniform1i(Uniform_names::texture, static_cast<int32_t>(Texture_slot::texture));
    shader->set_uniform1i(Uniform_names::has_texture, static_cast<int32_t>(m_textures.contains(Texture_slot::texture)));
    shader->set_uniform1i(Uniform_names::shadow_map, static_cast<int32_t>(Texture_slot::shadow_map));
}

void Material::bind_textures()
{
	for (auto& texture : m_textures)
	{
		texture.second->bind(texture.first);
	}
}

void Material::unbind_texture()
{
	for (auto& texture : m_textures)
	{
		texture.second->unbind();
	}
}


