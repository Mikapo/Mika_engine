#pragma once

#include "../Renderer_item.h"
#include <cstdint>
#include <vector>

namespace OpenGL
{
    class Index_buffer : public Renderer_item
    {
    public:
        Index_buffer(std::vector<uint32_t> indices) noexcept;
        ~Index_buffer();
        Index_buffer(const Index_buffer&) = delete;
        Index_buffer(Index_buffer&&) = delete;

        Index_buffer& operator=(const Index_buffer&) = delete;
        Index_buffer& operator=(Index_buffer&&) = delete;

        void bind() const noexcept override;
        void unbind() const noexcept override;

        [[nodiscard]] size_t get_count() const noexcept;

    protected:
        uint32_t construct_item() override;

    private:
        size_t m_count;
        std::vector<uint32_t> m_local_buffer;
    };
} // namespace OpenGL
