#pragma once

#include "Rendering/Buffers/Buffers.h"
#include <memory>


class Shader;
class Mesh
{
public:
    Mesh(std::unique_ptr<Buffers> buffers) noexcept;

	void bind_buffers() const;
    void unbind_buffers() const;
    size_t get_indices_count() const noexcept;

private:
	std::unique_ptr<Buffers> m_buffers;
};

