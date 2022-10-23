#pragma once

#include "OpenGL/Buffers/Buffers.h"
#include "OpenGL/Texture/Texture.h"
#include <future>
#include <string_view>
#include <unordered_map>

namespace MEngine
{
    class OpenGL_buffers
    {
    public:
        using Buffer_future = std::future<std::unique_ptr<OpenGL::Buffers>>;

        /**
         * @param Path to mesh
         * @return Returns buffers if they are not ready returns nullptr
         */
        [[nodiscard]] OpenGL::Buffers* get_object_buffers(const std::string& path);

        /**
         * @param Path to texture
         * @return Returns texture buffers if they are not ready returns nullptr
         */
        [[nodiscard]] OpenGL::Texture* get_texture(const std::string& path);

        // Clears all buffers
        void clear() noexcept;

    private:
        void create_object_buffers(const std::string& path);

        std::unordered_map<std::string, std::unique_ptr<OpenGL::Buffers>> m_ready_object_buffers;
        std::unordered_map<std::string, Buffer_future> m_future_object_buffers;
        std::unordered_map<std::string, std::unique_ptr<OpenGL::Texture>> m_textures;
    };
} // namespace MEngine
