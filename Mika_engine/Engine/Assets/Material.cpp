#include "Material.h"

#include "Utility/Uniform_names.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <stdexcept>

namespace Mika_engine
{
    void Material::add_texture(std::shared_ptr<OpenGL::Texture> texture)
    {
        m_textures.emplace(texture->get_slot(), texture);
    }

    void Material::remove_texture(OpenGL::Texture_slot slot) noexcept
    {
        m_textures.erase(slot);
    }

    void Material::update_shader(OpenGL::Shader* shader) const
    {
        if (!shader)
            throw std::invalid_argument("shader was null");

        shader->set_uniform(Uniform_names::ambient, m_ambient.x, m_ambient.y, m_ambient.z, m_ambient.w);
        shader->set_uniform(Uniform_names::diffuse, m_diffuse.x, m_diffuse.y, m_diffuse.z, m_diffuse.w);
        shader->set_uniform(Uniform_names::specular, m_specular.x, m_specular.y, m_specular.z, m_specular.w);
        shader->set_uniform(Uniform_names::shininess, m_shininess);
        shader->set_uniform(
            Uniform_names::default_color, m_default_color.r, m_default_color.g, m_default_color.b, m_default_color.a);

        shader->set_sampler_uniform(Uniform_names::texture, OpenGL::Texture_slot::color);
        shader->set_uniform(
            Uniform_names::has_texture, static_cast<int32_t>(m_textures.contains(OpenGL::Texture_slot::color)));
        shader->set_sampler_uniform(Uniform_names::shadow_map, OpenGL::Texture_slot::depth_map);
    }

    void Material::bind_textures() noexcept
    {
        for (auto& texture : m_textures)
        {
            if (!texture.second->has_been_initialized())
                texture.second->initialize();

            texture.second->bind();
        }
    }

    void Material::unbind_texture() noexcept
    {
        for (const auto& texture : m_textures)
            texture.second.get()->unbind();
    }

} // namespace Mika_engine
