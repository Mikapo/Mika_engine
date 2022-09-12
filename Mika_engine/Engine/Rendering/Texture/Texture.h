#pragma once

#include "Texture_base.h"
#include "Texture_buffer.h"
#include "Texture_slots.h"
#include <string>
#include <utility>

namespace OpenGL
{
    class Texture : public Texture_base
    {
    public:
        Texture(Texture_buffer buffer, Texture_slot slot);
        ~Texture() override = default;

        Texture(const Texture&) = delete;
        Texture(Texture&&) = delete;

        Texture& operator=(const Texture&) = delete;
        Texture& operator=(Texture&&) = delete;

    private:
        [[nodiscard]] uint32_t construct_item() override;

        Texture_buffer m_buffer;  
    };
} // namespace OpenGL
