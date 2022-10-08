#include "GL/glew.h"

#include "Texture_base.h"
#include <stdexcept>

OpenGL::Texture_base::~Texture_base()
{
    if (!has_been_initialized())
        return;

    const uint32_t texture_id = get_id();
    glDeleteTextures(1, &texture_id);
}

void OpenGL::Texture_base::bind() const noexcept
{
    glActiveTexture(GL_TEXTURE0 + static_cast<Underlying_slot_type>(m_slot));
    glBindTexture(GL_TEXTURE_2D, get_id());
}

void OpenGL::Texture_base::unbind() const noexcept
{
    glActiveTexture(GL_TEXTURE0 + static_cast<Underlying_slot_type>(m_slot));
    glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGL::Texture_base::set_slot(Texture_slot slot) noexcept
{
    m_slot = slot;
}

uint32_t OpenGL::Texture_base::construct_item()
{
    uint32_t texture_id = 0;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    return texture_id;
}
