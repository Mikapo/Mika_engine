#pragma once

#include <cstdint>

namespace OpenGL
{
    class Vertex_buffer_elements
    {
    public:
        Vertex_buffer_elements(uint32_t type, int32_t count, unsigned char normalized) noexcept;

        [[nodiscard]] uint32_t get_type() const noexcept;
        [[nodiscard]] uint32_t get_count() const noexcept;
        [[nodiscard]] unsigned char get_normalized() const noexcept;
        [[nodiscard]] static int32_t get_size_of_type(uint32_t type);

    private:
        uint32_t m_type;
        int32_t m_count;
        unsigned char m_normalized;
    };

} // namespace OpenGL
