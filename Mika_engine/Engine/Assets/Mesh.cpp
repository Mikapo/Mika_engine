#include "Mesh.h"

namespace Mika_engine
{
    Mesh::Mesh(std::unique_ptr<OpenGL::Buffers> buffers) noexcept
    {
        m_buffers = std::move(buffers);
    }

    void Mesh::bind_buffers() const
    {
        m_buffers->bind();
    }

    void Mesh::unbind_buffers() const
    {
        m_buffers->unbind();
    }

    size_t Mesh::get_indices_count() const noexcept
    {
        return m_buffers->get_indices_count();
    }

    OpenGL::Buffers* Mesh::get_buffers() noexcept
    {
        return m_buffers.get();
    }
} // namespace Mika_engine
