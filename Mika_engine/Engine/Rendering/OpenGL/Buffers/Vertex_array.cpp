#include "GL/glew.h"

#include "../layout/Vertex_buffer_layout.h"
#include "Vertex_array.h"
#include "Vertex_buffer.h"

OpenGL::Vertex_array::~Vertex_array()
{
    if (!has_been_initialized())
        return;

    const uint32_t array_id = get_id();
    glDeleteVertexArrays(1, &array_id);
}

void OpenGL::Vertex_array::add_buffer(const Vertex_buffer& vertex_buffer, const Vertex_buffer_layout& layout) const
{
    bind();
    vertex_buffer.bind();
    const auto& elements = layout.get_elements();

    // Pointer that is used to spesify offset of each element
    char* offset_ptr = nullptr;

    for (GLuint i = 0; i < elements.size(); i++)
    {
        const auto& element = elements.at(i);
        glEnableVertexAttribArray(i);

        glVertexAttribPointer(
            i,                                         // Index
            static_cast<GLint>(element.get_count()),   // Zmount of values in element. Must be 1 - 4
            element.get_type(),                        // Type of element
            element.get_normalized(),                  // Normalized bettween 0 and 1
            static_cast<GLsizei>(layout.get_stride()), // Size of vertex
            offset_ptr);                               // Offset of element in vertex

        // Adds offset to pointer
        offset_ptr += element.get_count() * Vertex_buffer_elements::get_size_of_type(element.get_type());
    }
}

void OpenGL::Vertex_array::bind() const noexcept
{
    glBindVertexArray(get_id());
}

void OpenGL::Vertex_array::unbind() const noexcept
{
    glBindVertexArray(0);
}

uint32_t OpenGL::Vertex_array::construct_item()
{
    uint32_t array_id = 0;
    glGenVertexArrays(1, &array_id);

    return array_id;
}
