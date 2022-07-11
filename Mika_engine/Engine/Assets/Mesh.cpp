#include "Mesh.h"


Mesh::Mesh(std::unique_ptr<Buffers> buffers) noexcept
{ 
	m_buffers = std::move(buffers); 
}

void Mesh::bind_buffers() const
{ 
	m_buffers->bind(); 
}

void Mesh::unbind_buffers() const 
{ 
	m_buffers->unbind(); 
}

size_t Mesh::get_indices_count() const noexcept
{ 
	return m_buffers->get_indices_count(); 
}
