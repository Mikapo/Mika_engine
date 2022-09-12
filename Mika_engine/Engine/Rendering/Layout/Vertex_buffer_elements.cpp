#include "GL/glew.h"

#include "Vertex_buffer_elements.h"
#include <stdexcept>

OpenGL::Vertex_buffer_elements::Vertex_buffer_elements(uint32_t type, int32_t count, unsigned char normalized) noexcept
    : m_type(type), m_count(count), m_normalized(normalized)
{
}

uint32_t OpenGL::Vertex_buffer_elements::get_type() const noexcept
{
    return m_type;
}

uint32_t OpenGL::Vertex_buffer_elements::get_count() const noexcept
{
    return m_count;
}

unsigned char OpenGL::Vertex_buffer_elements::get_normalized() const noexcept
{
    return m_normalized;
}

int32_t OpenGL::Vertex_buffer_elements::get_size_of_type(uint32_t type)
{
    switch (type)
    {
    case GL_FLOAT:
    case GL_UNSIGNED_INT:
        return 4;
    case GL_BYTE:
        return 1;
    default:
        throw std::invalid_argument("Type is not supported");
    }
}
