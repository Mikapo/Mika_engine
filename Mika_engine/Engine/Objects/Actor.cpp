#include "Actor.h"
#include "Components/Scene_components/Camera_component.h"
#include "Components/Scene_components/Collision_component.h"
#include "Core/Mika_engine.h"

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

void Actor::set_transform(Transform new_transform, bool check_for_collision)
{
	if (!check_for_collision || !check_collisions(new_transform))
	{
        m_transform = new_transform;
        update_local_coordinate_system();
        m_on_transform_change.broadcast(this);
	}
}

void Actor::set_location(glm::vec3 new_location, bool check_for_collision)
{
	Transform transform = get_transform();
	transform.m_location = new_location;
	set_transform(transform, check_for_collision);
}

void Actor::set_rotation(Rotator new_rotation, bool check_for_collision)
{ 
	Transform transform = get_transform();  
	transform.m_rotation = new_rotation;
    set_transform(transform, check_for_collision);
}

void Actor::set_scale(glm::vec3 new_scale, bool check_for_collision)
{ 
	Transform transform = get_transform(); 
	transform.m_scale = new_scale;
    set_transform(transform, check_for_collision);
}

glm::vec3 Actor::get_location() const 
{ 
	return m_transform.m_location; 
}

Rotator Actor::get_rotation() const 
{ 
	return m_transform.m_rotation; 
}

glm::vec3 Actor::get_scale() const 
{ 
	return m_transform.m_scale; 
}

void Actor::set_active_camera(Camera_component* camera)
{
    if (is_valid(m_active_camera))
        m_active_camera->m_on_being_destroyed.remove_object(this);

	m_active_camera = camera;
    camera->m_on_being_destroyed.add_object(this, &Actor::on_active_camera_being_destroyed);
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
	return m_directional_vectors.m_forward; 
}

glm::vec3 Actor::get_up_vector()
{ 
	return m_directional_vectors.m_up; 
}

bool Actor::check_collisions(std::optional<Transform> transform) 
{ 
	for (auto* collision_component : m_collisions)
    {
        auto collision = collision_component->check_for_collisions(transform);

		if (collision.has_value())
		{
            m_on_collision_detected.broadcast(collision_component, collision.value());
            return true;
		}
	}

	return false;
}

Actor_component* Actor::create_component(Class_obj* class_obj) 
{ 
	Actor_component* component = class_obj->construct_cast<Actor_component>(get_engine());
	if(!component)
		return nullptr;

    component->set_owner(this);
    component->set_world(get_world());
    component->m_on_being_destroyed.add_object(this, &Actor::on_component_destroyed);
    component->initialize();

    if (auto* collision = dynamic_cast<Collision_component*>(component))
    {
        collision->m_on_being_destroyed.add_object(this, &Actor::on_collision_component_destroyed);
        m_collisions.insert(collision);
    }

	m_components.insert(component);

    return component;
}

void Actor::add_local_offset(glm::vec3 offset, bool check_for_collision)
{
	Transform transform = get_transform();
	
	transform.m_location += m_directional_vectors.m_forward * offset.x;
    transform.m_location += m_directional_vectors.m_right * offset.y;
    transform.m_location += m_directional_vectors.m_up * offset.z;

	set_transform(transform, check_for_collision);
}

void Actor::add_world_offset(glm::vec3 offset, bool check_for_collision) 
{ 
	Transform transform = get_transform(); 
	
	transform.m_location += offset;

	set_transform(transform, check_for_collision);
}

void Actor::add_rotation_offset(Rotator rotation, bool check_for_collision)
{
	Transform transform = get_transform();

	transform.m_rotation = transform.m_rotation + rotation;

	set_transform(transform, check_for_collision);
}

void Actor::update_local_coordinate_system()
{
    m_directional_vectors = get_transform().m_rotation.calculate_directional_vectors_from_rotation();
}

void Actor::on_component_destroyed(Object* component) 
{ 
	remove_object_from_set(m_components, component); 
}

void Actor::on_collision_component_destroyed(Object* collision) 
{
	remove_object_from_set(m_collisions, collision); 
}

void Actor::on_active_camera_being_destroyed(Object* camera) 
{ 
	if (m_active_camera == camera)
        m_active_camera = nullptr;
}
