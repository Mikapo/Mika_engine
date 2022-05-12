#include "Actor.h"

#include "Components/Scene_components/Camera_component.h"
#include <glm/ext/matrix_transform.hpp>
#include <iostream>

void Actor::initialize()
{
	Object::initialize();

	update_local_coordinate_system();
}

void Actor::update(float deltatime)
{
	Object::update(deltatime);

	update_owned_objects(m_components, deltatime);
}

void Actor::get_owned_objects(std::vector<Object*>& out_array)
{
	Object::get_owned_objects(out_array);

	for (Actor_component* component : m_components)
		out_array.push_back(component);
}

World* Actor::get_world() const
{
	return m_owning_world;
}

void Actor::set_world(World* world)
{
	m_owning_world = world;
}

void Actor::set_transform(Transform new_transform)
{
	m_transform = new_transform;
	update_local_coordinate_system();
	m_on_transform_change.call(this);
}

void Actor::set_location(glm::vec3 new_location)
{
	Transform transform = get_transform();
	transform.m_location = new_location;
	set_transform(transform);
}

void Actor::set_active_camera(Camera_component* camera)
{
	m_active_camera = camera;
}

Transform Actor::get_transform() const
{
	return m_transform;
}

Camera_data Actor::get_active_camera_data()
{
	if (m_active_camera && get_engine()->is_object_valid(m_active_camera))
		return m_active_camera->get_camera_data();
	else
	{
		m_active_camera = nullptr;
		return Camera_data();
	}
}

glm::vec3 Actor::get_forward_vector()
{
	return m_local_coordinate_system.m_forward;
}

glm::vec3 Actor::get_up_vector()
{
	return m_local_coordinate_system.m_up;
}

void Actor::add_local_offset(glm::vec3 offset)
{
	Transform transform = get_transform();
	
	transform.m_location += m_local_coordinate_system.m_forward * offset.x;
	transform.m_location += m_local_coordinate_system.m_right * offset.y;
	transform.m_location += m_local_coordinate_system.m_up * offset.z;

	set_transform(transform);
}

void Actor::add_rotation_offset(Rotator rotation)
{
	Transform transform = get_transform();

	transform.m_rotation = transform.m_rotation + rotation;

	set_transform(transform);
}

void Actor::update_local_coordinate_system()
{
	m_local_coordinate_system = get_transform().m_rotation.calculate_coordinate_system_from_rotation();
}
