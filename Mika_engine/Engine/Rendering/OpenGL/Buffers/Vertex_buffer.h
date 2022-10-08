#pragma once

#include "../Renderer_item.h"
#include <utility>
#include <vector>

namespace OpenGL
{
    class Vertex_buffer : public Renderer_item
    {
    public:
        Vertex_buffer(std::vector<float> buffer) noexcept;
        ~Vertex_buffer();
        Vertex_buffer(const Vertex_buffer&) = delete;
        Vertex_buffer(Vertex_buffer&&) = delete;

        Vertex_buffer& operator=(const Vertex_buffer&) = delete;
        Vertex_buffer& operator=(Vertex_buffer&&) = delete;

        void bind() const noexcept override;
        void unbind() const noexcept override;

    protected:
        uint32_t construct_item() override;

    private:
        std::vector<float> m_local_buffer;
    };
} // namespace OpenGL
