#pragma once

#include "../Layout/Vertex_buffer_layout.h"
#include "Index_buffer.h"
#include "Vertex_array.h"
#include "Vertex_buffer.h"
#include <memory>
#include <vector>

namespace OpenGL
{
    class Buffers
    {
    public:
        Buffers(std::vector<float> vertices, std::vector<uint32_t> indices, Vertex_buffer_layout layout) noexcept;

        // Binds vertex array and index buffer
        void bind() const noexcept;

        // Unbinds vertex array and index buffer
        void unbind() const noexcept;

        [[nodiscard]] size_t get_indices_count() const noexcept;
        [[nodiscard]] bool has_been_initialized() const noexcept;

        // Initializes all buffers
        void initialize();

    private:
        Vertex_buffer m_vertex_buffer;
        Vertex_array m_vertex_array;
        Index_buffer m_index_buffer;
        Vertex_buffer_layout m_layout;
    };
} // namespace OpenGL
