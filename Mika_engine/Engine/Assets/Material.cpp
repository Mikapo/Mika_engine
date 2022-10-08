#include "Material.h"

namespace Mika_engine
{
    void Material::add_texture(const std::string& texture_location, Texture_slot slot)
    {
        m_textures.emplace(slot, texture_location);
    }

    void Material::remove_texture(Texture_slot slot) noexcept
    {
        m_textures.erase(slot);
    }

    const std::unordered_map<Texture_slot, Texture_data>& Material::get_textures() const noexcept
    {
        return m_textures;
    }

} // namespace Mika_engine
