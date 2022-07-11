#include "Texture.h"

#include "stb_image/stb_Image.h"
#include <string>


Texture::Texture(std::string_view path) : m_filepath(path)
{
    stbi_set_flip_vertically_on_load(1);
    m_local_buffer = stbi_load(path.data(), &m_width, &m_height, &m_bpp, 4);
}

Texture::~Texture() 
{ 
    if (is_valid())
    {
        glDeleteTextures(1, &m_id);
        release_local_buffer();
    }
}

void Texture::bind(Texture_slot slot) noexcept
{
    if (!m_has_been_initialized)
    {
        initialize();
        release_local_buffer();
    }

    m_is_binded = true;
    m_current_slot = GL_TEXTURE0 + static_cast<int32_t>(slot);
    glActiveTexture(m_current_slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() noexcept
{ 
    if (!m_is_binded)
        return; 

    glActiveTexture(m_current_slot);
    glBindTexture(GL_TEXTURE_2D, 0); 
    m_current_slot = -1;
    m_is_binded = false;
}

void Texture::initialize() noexcept
{
    if (m_local_buffer)
    {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        m_has_been_initialized = true;
    }
}

void Texture::release_local_buffer() noexcept
{
    if (m_local_buffer)
    {
        stbi_image_free(m_local_buffer);
        m_local_buffer = nullptr;
    }
}
