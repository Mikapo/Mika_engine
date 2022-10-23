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

    // Class that spesifies shader settings for mesh
    class Material
    {
    public:
        glm::vec4 m_ambient = {0.1f, 0.1f, 0.1f, 1.0f};
        glm::vec4 m_diffuse = {1.0f, 1.0f, 1.0f, 1.0f};
        glm::vec4 m_specular = {5.0f, 5.0f, 5.0f, 1.0f};
        glm::vec4 m_default_color = {0.6f, 0.6f, 0.6f, 1.0f};
        float m_shininess = 200.0f;

        /**
         * Adds texture to thematerial
         *
         * @param File path where texture is located
         * @param What texture slot to use in shader
         */
        void add_texture(const std::string& texture_location, Texture_slot slot = Texture_slot::color);

        /** Remove texture from the material
         *
         * @param The slot of texture which to remove
         */
        void remove_texture(Texture_slot slot = Texture_slot::color) noexcept;

        /**
         * @return All textures that this material has
         */
        [[nodiscard]] const std::unordered_map<Texture_slot, Texture_data>& get_textures() const noexcept;

    private:
        std::unordered_map<Texture_slot, Texture_data> m_textures;
    };
} // namespace MEngine
