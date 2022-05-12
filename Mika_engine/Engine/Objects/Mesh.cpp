#include "Mesh.h"
#include "Rendering/Model_loader.h"
#include "Utility/Uniform_names.h"
#include "Rendering/Shading/Shader.h"

void Mesh::set_material(Material new_material)
{
	m_material = new_material;
}

Material Mesh::get_material() const
{
	return m_material;
}

void Mesh::set_buffers(std::shared_ptr<Buffers> buffers)
{
	m_buffers = buffers;
}

std::shared_ptr<Buffers> Mesh::get_buffers() const
{
	return m_buffers;
}
