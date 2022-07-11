#include "Mesh_component.h"

#include "Rendering/Model_loader.h"
#include "Objects/World.h"
#include "Assets/Mesh.h"
#include "Objects/Actor.h"

void Mesh_component::initialize()
{
	Scene_component::initialize();

	get_world()->register_mesh_component(this);
}

void Mesh_component::set_mesh(std::shared_ptr<Mesh> mesh) noexcept 
{ 
	m_mesh = mesh; 
}

void Mesh_component::set_material(const Material& material) noexcept 
{ 
	m_material = material; 
}

Material Mesh_component::get_material() const noexcept
{ 
	return m_material;
}

std::optional<Mesh_data> Mesh_component::get_mesh_data() const noexcept
{
    if (!m_mesh)
		return std::optional<Mesh_data>();

	Mesh_data mesh_data = { get_world_transform(), m_mesh, m_material };
	return mesh_data;
}



