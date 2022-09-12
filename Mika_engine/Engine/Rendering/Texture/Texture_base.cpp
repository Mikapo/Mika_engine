#include "GL/glew.h"

#include "Texture_base.h"
#include <stdexcept>

OpenGL::Texture_base::Texture_base(Texture_slot slot) : m_slot(slot)
{
    if (static_cast<Underlying_slot_type>(slot) > MAX_SUPPORTED_TEXTURE_SLOT)
        throw std::invalid_argument("Texture slot is not supported");
}

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

OpenGL::Texture_slot OpenGL::Texture_base::get_slot() const noexcept 
{
    return m_slot;
}

uint32_t OpenGL::Texture_base::construct_item()
{
    uint32_t texture_id = 0;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    return texture_id;
}
