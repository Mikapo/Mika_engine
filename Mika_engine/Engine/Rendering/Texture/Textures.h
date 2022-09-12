#pragma once

#include "Texture.h"
#include <memory>

namespace OpenGL
{
    class Textures
    {
    public:
        Textures() = delete;

        static std::unique_ptr<Texture> load_texture_from_file(
            std::string_view file_path, Texture_slot slot, bool initialize = true);
        static std::unique_ptr<Texture> create_texture_with_buffer(
            std::vector<unsigned char> buffer, int32_t tex_width, int32_t tex_height, Texture_slot slot,
            bool initialize = true);

    private:
        static std::unique_ptr<Texture> create_texture(Texture_buffer buffer, Texture_slot slot, bool initialize);
    };
} // namespace OpenGL
