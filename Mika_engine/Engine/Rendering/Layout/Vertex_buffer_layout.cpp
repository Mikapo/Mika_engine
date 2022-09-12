#include "GL/glew.h"

#include "Vertex_buffer_layout.h"
#include <stdexcept>

void OpenGL::Vertex_buffer_layout::push_float(int32_t count)
{
    push(GL_FLOAT, count);
}

void OpenGL::Vertex_buffer_layout::push_uint(int32_t count)
{
    push(GL_UNSIGNED_INT, count);
}

void OpenGL::Vertex_buffer_layout::push_ubyte(int32_t count)
{
    push(GL_UNSIGNED_BYTE, count);
}

void OpenGL::Vertex_buffer_layout::push(uint32_t type, int32_t count)
{
    if (count < 1 || count > 4)
        throw std::invalid_argument("Count needs to be between 1 - 4");

    m_elements.emplace_back(type, count, GL_TRUE);
    m_stride += count * Vertex_buffer_elements::get_size_of_type(type);
}

const std::vector<OpenGL::Vertex_buffer_elements>& OpenGL::Vertex_buffer_layout::get_elements() const noexcept
{
    return m_elements;
}

uint32_t OpenGL::Vertex_buffer_layout::get_stride() const noexcept
{
    return m_stride;
}
