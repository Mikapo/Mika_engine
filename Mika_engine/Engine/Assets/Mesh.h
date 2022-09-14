#pragma once

#include "Rendering/Buffers/Buffers.h"
#include <memory>

class Shader;

namespace Mika_engine
{
    class Mesh
    {
    public:
        Mesh(std::unique_ptr<OpenGL::Buffers> buffers) noexcept;

        void bind_buffers() const;
        void unbind_buffers() const;
        size_t get_indices_count() const noexcept;
        [[nodiscard]] OpenGL::Buffers* get_buffers() noexcept;

    private:
        std::unique_ptr<OpenGL::Buffers> m_buffers;
    };
} // namespace Mika_engine
