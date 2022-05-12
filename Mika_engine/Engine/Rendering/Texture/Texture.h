#pragma once

#include "Rendering/Renderer_item.h"

#include <utility>
#include <string>
#include "GL/glew.h"
#include "Texture_slots.h"

class Texture : public Renderer_item
{
public:
    Texture(std::string_view path);
    ~Texture();

    void bind(Texture_slot slot = Texture_slot::texture);
    static void unbind();

    inline int32_t GetWidth() const { return m_width; }

private:
    void initialize();
    void release_local_buffer();

    bool m_has_been_initialized = false;
    std::string m_filepath;
    unsigned char* m_local_buffer = nullptr;
    int32_t m_width = 0, m_height = 0, m_bpp = 0;
};
