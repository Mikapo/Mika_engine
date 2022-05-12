#include "Mesh_component.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "Rendering/Model_loader.h"
#include "Objects/World.h"
#include "Objects/Mesh.h"
#include "Objects/Actor.h"

void Mesh_component::update(float deltatime)
{
	Scene_component::update(deltatime);

	if (is_valid(m_mesh))
		m_mesh->update(deltatime);
}

void Mesh_component::initialize()
{
	Scene_component::initialize();

	get_world()->register_mesh_component(this);
}

void Mesh_component::load_mesh_from_file(std::string_view file, int32_t mesh_index)
{
	auto buffers = Model_loader::load(file, mesh_index);

	Mesh* mesh = Object::construct_object<Mesh>(get_engine());
	mesh->set_buffers(buffers);
	m_mesh = mesh;
	
}

void Mesh_component::set_material_to_current_mesh(const Material& material)
{
	if (m_mesh && get_engine()->is_object_valid(m_mesh))
		m_mesh->set_material(material);
}

void Mesh_component::get_owned_objects(std::vector<Object*>& out_array)
{
	Actor_component::get_owned_objects(out_array);

	if(m_mesh)
		out_array.push_back(m_mesh);
}

std::optional<Mesh_data> Mesh_component::get_mesh_data()
{
	if (!is_valid(m_mesh))
		return std::optional<Mesh_data>();

	auto buffers = m_mesh->get_buffers();

	Mesh_data mesh_data = { get_world_transform(), buffers, m_mesh->get_material() };
	return mesh_data;
}



