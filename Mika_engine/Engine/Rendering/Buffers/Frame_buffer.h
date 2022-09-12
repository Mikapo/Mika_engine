#pragma once
#include "../Renderer_item.h"

namespace OpenGL
{
    class Frame_buffer : public Renderer_item
    {
    public:
        Frame_buffer() = default;
        ~Frame_buffer() override;

        Frame_buffer(const Frame_buffer&) = delete;
        Frame_buffer(Frame_buffer&&) = delete;

        Frame_buffer& operator=(const Frame_buffer&) = delete;
        Frame_buffer& operator=(Frame_buffer&&) = delete;

        void bind() const noexcept override;
        void unbind() const noexcept override;

    protected:
        uint32_t construct_item() override;
    };

} // namespace OpenGL
