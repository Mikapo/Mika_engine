#include "GL/glew.h"

#include "Shader.h"
#include "Shadow_map.h"
#include <stdexcept>

OpenGL::Shadow_map::Shadow_map() : m_depth_map(1500, 1500)
{
}

void OpenGL::Shadow_map::init(std::unique_ptr<Shader> shadow_map_shader)
{
    if (m_has_been_initialized)
        throw std::logic_error("Shadow map has been already initialized");

    m_shader = std::move(shadow_map_shader);

    m_frame_buffer.initialize();
    m_frame_buffer.bind();

    m_depth_map.initialize();
    m_depth_map.add_depth_map_to_framebuffer();

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    m_frame_buffer.unbind();

    m_has_been_initialized = true;
}

void OpenGL::Shadow_map::bind_frame_buffer() const noexcept
{
    m_frame_buffer.bind();
}

void OpenGL::Shadow_map::unbind_frame_buffer() const noexcept
{
    m_frame_buffer.unbind();
}

void OpenGL::Shadow_map::bind_depth_map() const noexcept
{
    m_depth_map.bind();
}

void OpenGL::Shadow_map::unbind_depth_map() const noexcept
{
    m_depth_map.unbind();
}

OpenGL::Shader* OpenGL::Shadow_map::get_shader() const noexcept
{
    return m_shader.get();
}

void OpenGL::Shadow_map::get_shadow_resolution(int32_t& out_width, int32_t& out_height) const noexcept
{
    m_depth_map.get_resolution(out_width, out_height);
}
