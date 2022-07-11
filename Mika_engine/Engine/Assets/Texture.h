#pragma once

#include "Rendering/Renderer_item.h"

#include <utility>
#include <string>
#include "GL/glew.h"
#include "Rendering/Texture/Texture_slots.h"

class Texture : public Renderer_item
{
public:
    Texture(std::string_view path);
    ~Texture();
    Texture(const Texture&) = delete;
    Texture(Texture&&) = default;

    void operator=(const Texture&) = delete;
    void operator=(Texture&&) = delete;

    void bind(Texture_slot slot) noexcept;
    void unbind() noexcept;
    inline int32_t get_width() const noexcept { return m_width; }

private:
    void initialize() noexcept;
    void release_local_buffer() noexcept;

    bool m_has_been_initialized = false;
    std::string m_filepath = "";
    bool m_is_binded = false;
    int32_t m_current_slot = -1;
    unsigned char* m_local_buffer = nullptr;
    int32_t m_width = 0, m_height = 0, m_bpp = 0;
};
