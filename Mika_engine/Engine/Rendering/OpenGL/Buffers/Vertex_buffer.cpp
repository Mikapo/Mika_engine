#include "GL/Glew.h"

#include "Vertex_buffer.h"

OpenGL::Vertex_buffer::Vertex_buffer(std::vector<float> buffer) noexcept : m_local_buffer(std::move(buffer))
{
}

OpenGL::Vertex_buffer::~Vertex_buffer()
{
    if (!has_been_initialized())
        return;

    const uint32_t buffer_id = get_id();
    glDeleteBuffers(1, &buffer_id);
}

void OpenGL::Vertex_buffer::bind() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, get_id());
}

void OpenGL::Vertex_buffer::unbind() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

uint32_t OpenGL::Vertex_buffer::construct_item()
{
    uint32_t buffer_id = 0;
    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);

    glBufferData(
        GL_ARRAY_BUFFER, sizeof(float) * m_local_buffer.size(), // Buffer size
        m_local_buffer.data(),                                  // Buffer data
        GL_STATIC_DRAW);                                        // Buffer will be static

    // Frees local buffer
    std::vector<float>().swap(m_local_buffer);

    return buffer_id;
}
