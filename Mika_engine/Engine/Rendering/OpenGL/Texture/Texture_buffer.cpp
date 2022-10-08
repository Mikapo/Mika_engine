#include "Texture_buffer.h"

#include "stb_image/stb_Image.h"
#include <span>
#include <stdexcept>

void OpenGL::Texture_buffer::load_buffer_from_file(std::string_view path)
{
    stbi_set_flip_vertically_on_load(1);

    int32_t bpp = 0;
    unsigned char* const texture_buffer = stbi_load(path.data(), &m_width, &m_height, &bpp, DESIRED_CHANNELS);

    if (texture_buffer == nullptr)
        throw std::invalid_argument("Failed to load the texture");

    const size_t tex_buffer_size = get_correct_buffer_size(m_width, m_height);
    const std::span tex_span = {texture_buffer, tex_buffer_size};

    m_buffer.resize(tex_buffer_size);
    std::copy(tex_span.begin(), tex_span.end(), m_buffer.begin());

    stbi_image_free(texture_buffer);
}

void OpenGL::Texture_buffer::add_buffer(std::vector<unsigned char> buffer, int32_t tex_width, int32_t tex_height)
{
    if (buffer.size() != get_correct_buffer_size(tex_height, tex_height))
        throw std::invalid_argument("Buffer is wrong size");

    m_buffer = std::move(buffer);
    m_width = tex_width;
    m_height = tex_height;
}

size_t OpenGL::Texture_buffer::get_correct_buffer_size(int32_t tex_width, int32_t tex_height) noexcept
{
    return static_cast<size_t>(tex_width * tex_height * DESIRED_CHANNELS);
}

void OpenGL::Texture_buffer::free_buffer() noexcept
{
    // frees buffer memory
    std::vector<unsigned char>().swap(m_buffer);
}

const std::vector<unsigned char>& OpenGL::Texture_buffer::get_buffer() const noexcept
{
    return m_buffer;
}

bool OpenGL::Texture_buffer::has_buffer() const noexcept
{
    return !m_buffer.empty();
}

void OpenGL::Texture_buffer::get_dimensions(int32_t& width, int32_t& height) const noexcept
{
    width = m_width;
    height = m_height;
}
