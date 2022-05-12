#pragma once

#include "Rendering/Renderer_item.h"

#include "GL/glew.h"
#include <utility>

class Vertex_buffer : public Renderer_item
{
public:
    Vertex_buffer(const void* data, GLsizeiptr size);
    ~Vertex_buffer();

    void bind() const;
    static void unbind();

};
