#pragma once

#include "OpenGL/Buffers/Buffers.h"
#include "OpenGL/Texture/Texture.h"
#include <future>
#include <string_view>
#include <unordered_map>

namespace Mika_engine
{
    class OpenGL_buffers
    {
    public:
        using Buffer_future = std::future<std::unique_ptr<OpenGL::Buffers>>;

        [[nodiscard]] OpenGL::Buffers* get_object_buffers(const std::string& path);
        [[nodiscard]] OpenGL::Texture* get_texture(const std::string& path);
        void clear() noexcept;

    private:
        void create_object_buffers(const std::string& path);

        std::unordered_map<std::string, std::unique_ptr<OpenGL::Buffers>> m_ready_object_buffers;
        std::unordered_map<std::string, Buffer_future> m_future_object_buffers;
        std::unordered_map<std::string, std::unique_ptr<OpenGL::Texture>> m_textures;
    };
} // namespace Mika_engine
