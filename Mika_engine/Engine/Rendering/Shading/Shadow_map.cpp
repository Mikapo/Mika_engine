#include "Shadow_map.h"

#include "Shader.h"
#include "Utility/Uniform_names.h"

Shadow_map::~Shadow_map()
{
    if (m_has_been_initialized)
    {
        cleanup();
    }
}

void Shadow_map::cleanup() noexcept
{
    glDeleteTextures(1, &m_depth_map);
    glDeleteFramebuffers(1, &m_frame_buffer);
    m_shader.reset();
    m_has_been_initialized = false;
}

void Shadow_map::init(int32_t shadow_width, int32_t shadow_height)
{
    if (m_has_been_initialized)
        return;

    m_shadow_width = shadow_width;
    m_shadow_height = shadow_height;

    m_shader = std::make_unique<Shader>("Engine/shaders/Shadow_map.frag", "Engine/shaders/Shadow_map.vert");
    m_depth_map = create_depth_map_texture(shadow_width, shadow_height);
    m_frame_buffer = create_frame_buffer(m_depth_map);
    m_has_been_initialized = true;
}

uint32_t Shadow_map::create_depth_map_texture(int32_t shadow_width, int32_t shadow_height) noexcept
{
    uint32_t depth_map = 0;
    glGenTextures(1, &depth_map);
    glBindTexture(GL_TEXTURE_2D, depth_map);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadow_width, shadow_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, 0);
    return depth_map;
}

uint32_t Shadow_map::create_frame_buffer(uint32_t depth_map) noexcept
{
    uint32_t frame_buffer = 0;
    glGenFramebuffers(1, &frame_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_map, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return frame_buffer;
}

void Shadow_map::bind_frame_buffer() const noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer);
}

void Shadow_map::unbind_frame_buffer() noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Shadow_map::bind_texture(Texture_slot slot) const noexcept
{
    glActiveTexture(GL_TEXTURE0 + static_cast<int32_t>(slot));
    glBindTexture(GL_TEXTURE_2D, m_depth_map);
}

void Shadow_map::unbind_texture() noexcept
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Shadow_map::get_shadow_resolution(int32_t& out_width, int32_t& out_height) const noexcept
{
    out_width = m_shadow_width;
    out_height = m_shadow_height;
}

void Shadow_map::update_shader(glm::mat4 light_space)
{
    m_shader->set_uniform(Uniform_names::light_space, light_space);
}
