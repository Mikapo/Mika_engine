#include "GL/glew.h"

#include "Depth_map.h"

OpenGL::Depth_map::Depth_map(int32_t width, int32_t height) noexcept
    : Texture_base(Texture_slot::depth_map), m_width(width), m_height(height)
{
}

void OpenGL::Depth_map::add_depth_map_to_framebuffer()
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, get_id(), 0);
}

void OpenGL::Depth_map::get_resolution(int32_t& out_width, int32_t& out_height) const noexcept
{
    out_width = m_width;
    out_height = m_height;
}

uint32_t OpenGL::Depth_map::construct_item()
{
    const uint32_t texture_id = Texture_base::construct_item();

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);

    return texture_id;
}
