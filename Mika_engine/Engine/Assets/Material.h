#pragma once

#include "Rendering/OpenGL/Texture/Texture_slots.h"
#include <glm/vec4.hpp>
#include <memory>
#include <unordered_map>

namespace OpenGL
{
    class Shader;
}

namespace MEngine
{
    using Texture_slot = OpenGL::Texture_slot;

    struct Texture_data
    {
        std::string texture_location;
    };

    class Material
    {
    public:
        glm::vec4 m_ambient = {0.1f, 0.1f, 0.1f, 1.0f};
        glm::vec4 m_diffuse = {1.0f, 1.0f, 1.0f, 1.0f};
        glm::vec4 m_specular = {5.0f, 5.0f, 5.0f, 1.0f};
        glm::vec4 m_default_color = {0.6f, 0.6f, 0.6f, 1.0f};
        float m_shininess = 200.0f;

        void add_texture(const std::string& texture_location, Texture_slot slot = Texture_slot::color);
        void remove_texture(Texture_slot slot = Texture_slot::color) noexcept;
        [[nodiscard]] const std::unordered_map<Texture_slot, Texture_data>& get_textures() const noexcept;

    private:
        std::unordered_map<Texture_slot, Texture_data> m_textures;
    };
} // namespace MEngine
