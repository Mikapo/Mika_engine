#include "OpenGL_buffers.h"
#include "OpenGL/Model_loader.h"
#include "OpenGL/Texture/Textures.h"

namespace MEngine
{
    OpenGL::Buffers* OpenGL_buffers::get_object_buffers(const std::string& path)
    {
        auto ready_buffer = m_ready_object_buffers.find(path);

        if (ready_buffer != m_ready_object_buffers.end())
            return ready_buffer->second.get();

        auto buffer_future = m_future_object_buffers.find(path);

        if (buffer_future == m_future_object_buffers.end())
        {
            create_object_buffers(path);
            return nullptr;
        }

        if (buffer_future->second._Is_ready())
        {
            auto buffers = buffer_future->second.get();
            buffers->initialize();
            m_ready_object_buffers.emplace(path, std::move(buffers));
            m_future_object_buffers.erase(buffer_future);
            return m_ready_object_buffers[path].get();
        }

        return nullptr;
    }

    OpenGL::Texture* OpenGL_buffers::get_texture(const std::string& path)
    {
        auto found_texture = m_textures.find(path);

        if (found_texture != m_textures.end())
            return found_texture->second.get();

        std::unique_ptr texture = OpenGL::Textures::load_texture_from_file(path);
        m_textures.emplace(path, std::move(texture));

        return m_textures.at(path).get();
    }

    void OpenGL_buffers::clear() noexcept
    {
        m_ready_object_buffers.clear();
        m_future_object_buffers.clear();
        m_textures.clear();
    }

    void OpenGL_buffers::create_object_buffers(const std::string& path)
    {
        Buffer_future new_buffers = std::async(std::launch::async, OpenGL::Model_loader::load, path, 0);
        m_future_object_buffers.emplace(path, std::move(new_buffers));
    }
} // namespace MEngine
