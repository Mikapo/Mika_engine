#pragma once

#include <cstdint>

namespace OpenGL
{
    class Renderer_item
    {
    public:
        virtual ~Renderer_item() = default;

        void initialize();
        [[nodiscard]] bool has_been_initialized() const noexcept;

        Renderer_item(const Renderer_item&) = delete;
        Renderer_item(Renderer_item&& other) = delete;

        Renderer_item& operator=(const Renderer_item&) = delete;
        Renderer_item& operator=(Renderer_item&& other) = delete;

        virtual void bind() const noexcept = 0;
        virtual void unbind() const noexcept = 0;

    protected:
        Renderer_item() = default;

        [[nodiscard]] virtual uint32_t construct_item() = 0;
        [[nodiscard]] uint32_t get_id() const noexcept;

    private:
        uint32_t m_id = 0;
        bool m_has_been_initialized = false;
    };

} // namespace OpenGL
