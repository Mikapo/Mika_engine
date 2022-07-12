#include "Material.h"

#include "Utility/Uniform_names.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <stdexcept>

void Material::add_texture(std::shared_ptr<Texture> texture, Texture_slot slot)
{
    m_textures.emplace(slot, texture);
}

void Material::remove_texture(Texture_slot slot) noexcept
{
    m_textures.erase(slot);
}

void Material::update_shader(Shader* shader) const
{
    if (!shader)
        throw std::invalid_argument("shader was null");

    shader->set_uniform4f(Uniform_names::ambient, m_ambient.x, m_ambient.y, m_ambient.z, m_ambient.w);
    shader->set_uniform4f(Uniform_names::diffuse, m_diffuse.x, m_diffuse.y, m_diffuse.z, m_diffuse.w);
    shader->set_uniform4f(Uniform_names::specular, m_specular.x, m_specular.y, m_specular.z, m_specular.w);
    shader->set_uniform1f(Uniform_names::shininess, m_shininess);
    shader->set_uniform4f(
        Uniform_names::default_color, m_default_color.r, m_default_color.g, m_default_color.b, m_default_color.a);

    shader->set_uniform1i(Uniform_names::texture, static_cast<int32_t>(Texture_slot::texture));
    shader->set_uniform1i(Uniform_names::has_texture, static_cast<int32_t>(m_textures.contains(Texture_slot::texture)));
    shader->set_uniform1i(Uniform_names::shadow_map, static_cast<int32_t>(Texture_slot::shadow_map));
}

void Material::bind_textures() noexcept
{
    for (auto& texture : m_textures)
        texture.second->bind(texture.first);
}

void Material::unbind_texture() noexcept
{
    for (const auto& texture : m_textures)
        texture.second.get()->unbind();
}
