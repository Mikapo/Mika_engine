#pragma once

#include "../Renderer_item.h"
#include "Texture_slots.h"
#include <type_traits>

namespace OpenGL
{
    class Texture_base : public Renderer_item
    {
    public:
        using Underlying_slot_type = std::underlying_type_t<Texture_slot>;

        Texture_base(Texture_slot slot);
        ~Texture_base() override;

        Texture_base(const Texture_base&) = delete;
        Texture_base(Texture_base&&) = delete;

        Texture_base& operator=(const Texture_base&) = delete;
        Texture_base& operator=(Texture_base&&) = delete;

        void bind() const noexcept override;
        void unbind() const noexcept override;
        [[nodiscard]] Texture_slot get_slot() const noexcept;

    protected:
        uint32_t construct_item() override;

    private:
        const Texture_slot m_slot = Texture_slot::color;

        constexpr static Underlying_slot_type MAX_SUPPORTED_TEXTURE_SLOT = 31;
    };
} // namespace OpenGL
