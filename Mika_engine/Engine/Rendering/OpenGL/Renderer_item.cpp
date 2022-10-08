#include "Renderer_item.h"

#include <stdexcept>
#include <utility>

void OpenGL::Renderer_item::initialize()
{
    if (m_has_been_initialized)
        throw std::logic_error("Already initialized");

    m_id = construct_item();
    m_has_been_initialized = true;
}

bool OpenGL::Renderer_item::has_been_initialized() const noexcept
{
    return m_has_been_initialized;
}

uint32_t OpenGL::Renderer_item::get_id() const noexcept
{
    return m_id;
}
