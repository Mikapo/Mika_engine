#include "Buffers.h"

OpenGL::Buffers::Buffers(
    std::vector<float> vertices, std::vector<uint32_t> indices, Vertex_buffer_layout layout) noexcept
    : m_vertex_buffer(std::move(vertices)), m_index_buffer(std::move(indices)), m_layout(std::move(layout))

{
}

void OpenGL::Buffers::bind() const noexcept
{
    m_vertex_array.bind();
    m_index_buffer.bind();
}

void OpenGL::Buffers::unbind() const noexcept
{
    m_vertex_array.unbind();
    m_index_buffer.unbind();
}

size_t OpenGL::Buffers::get_indices_count() const noexcept
{
    return m_index_buffer.get_count();
}

bool OpenGL::Buffers::has_been_initialized() const noexcept
{
    return m_vertex_array.has_been_initialized() && m_index_buffer.has_been_initialized();
}

void OpenGL::Buffers::initialize()
{
    m_vertex_buffer.initialize();
    m_vertex_array.initialize();
    m_index_buffer.initialize();

    m_vertex_array.add_buffer(m_vertex_buffer, m_layout);
}
