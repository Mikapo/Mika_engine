#include "GL/glew.h"

#include "Frame_buffer.h"

OpenGL::Frame_buffer::~Frame_buffer()
{
    if (!has_been_initialized())
        return;

    const uint32_t buffer_id = get_id();
    glDeleteFramebuffers(1, &buffer_id);
}

void OpenGL::Frame_buffer::bind() const noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, get_id());
}

void OpenGL::Frame_buffer::unbind() const noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

uint32_t OpenGL::Frame_buffer::construct_item()
{
    uint32_t buffer_id = 0;
    glGenFramebuffers(1, &buffer_id);

    return buffer_id;
}
