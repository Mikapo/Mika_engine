#pragma once

#include "Vertex_buffer_elements.h"
#include <vector>

namespace OpenGL
{
    class Vertex_buffer_layout
    {
    public:
        void push_float(int32_t count);
        void push_uint(int32_t count);
        void push_ubyte(int32_t count);

        [[nodiscard]] const std::vector<Vertex_buffer_elements>& get_elements() const noexcept;

        // Size of vertex using this layout
        [[nodiscard]] uint32_t get_stride() const noexcept;

    private:
        void push(uint32_t type, int32_t count);

        std::vector<Vertex_buffer_elements> m_elements;
        int32_t m_stride = 0;
    };
} // namespace OpenGL
