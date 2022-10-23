#include "Index_buffer.h"

#include "GL/glew.h"

OpenGL::Index_buffer::Index_buffer(std::vector<uint32_t> indices) noexcept
    : m_count(indices.size()), m_local_buffer(std::move(indices))
{
}

OpenGL::Index_buffer::~Index_buffer()
{
    if (!has_been_initialized())
        return;

    const uint32_t buffer_id = get_id();
    glDeleteBuffers(1, &buffer_id);
}

void OpenGL::Index_buffer::bind() const noexcept
{
    const uint32_t buffer_id = get_id();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
}

void OpenGL::Index_buffer::unbind() const noexcept
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

size_t OpenGL::Index_buffer::get_count() const noexcept
{
    return m_count;
}

uint32_t OpenGL::Index_buffer::construct_item()
{
    uint32_t buffer_id = 0;
    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,                             // Buffer Type
        static_cast<GLsizeiptr>(sizeof(uint32_t) * m_count), // Buffer Size
        m_local_buffer.data(),                               // Buffer Data
        GL_STATIC_DRAW);                                     // Buffer will be static

    // Frees local buffer
    std::vector<uint32_t>().swap(m_local_buffer);

    return buffer_id;
}
