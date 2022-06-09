#include "World.h"

#include "Components/Scene_components/Mesh_component.h"
#include "Components/Scene_components/Light_component.h"
#include "Components/Scene_components/Collision_component.h"
#include "Objects/UI/UI.h"
#include "Core/Mika_engine.h"


void World::update(float deltatime)
{
	Object::update(deltatime);

	update_owned_objects(m_actors, deltatime);
	update_owned_objects(m_viewport, deltatime);
}

void World::get_owned_objects(std::vector<Object*>& out_array)
{
	Object::get_owned_objects(out_array);
	
	for (Actor* actor : m_actors)
		out_array.push_back(actor);

	for (UI* ui : m_viewport)
		out_array.push_back(ui);
}

Actor* World::spawn_actor(Class_obj* class_obj, Transform transform) 
{ 
	Actor* actor = class_obj->construct_cast<Actor>(get_engine());
	if(!actor)
		return nullptr;

	m_actors.insert(actor);
    actor->m_on_being_destroyed.add_object(this, &World::on_actor_destroyed);
    actor->set_world(this);
    actor->set_transform(transform);
    actor->initialize();
    return actor;
}

UI* World::create_ui(Class_obj* class_obj) 
{ 
	UI* ui = class_obj->construct_cast<UI>(get_engine());
    if (!ui)
        return nullptr;

    ui->initialize();
    return ui;
}

void World::register_mesh_component(Mesh_component* component)
{
	m_mesh_components.insert(component);
    component->m_on_being_destroyed.add_object(this, &World::on_registered_mesh_destroyed);
}

void World::register_light_component(Light_component* component)
{
	m_lights.insert(component); 
	component->m_on_being_destroyed.add_object(this, &World::on_registered_light_destroyed);
}

void World::register_collision_component(std::shared_ptr<Collision> collision, Collision_component* component)
{ 
	m_collisions.insert(component); 
	m_collision_handler.update_component(component, collision);
	component->m_on_being_destroyed.add_object(this, &World::on_registered_collision_destroyed);
}

void World::update_collisions(std::shared_ptr<Collision> collision, Collision_component* component)
{
	m_collision_handler.update_component(component, collision); 
}

std::optional<Collision_component*> World::find_collisions(
    Collision* collision, const Collision_component* component) const
{
    return m_collision_handler.find_collisions(collision, component);
}

void World::send_data_to_render()
{
	for (Mesh_component* component : m_mesh_components)
	{
		if (!is_valid(component))
			continue;

		auto mesh_data = component->get_mesh_data();

		if(mesh_data.has_value())
			get_engine()->send_mesh_to_render(mesh_data.value());
	}

	for (Light_component* light : m_lights)
	{
		if (!is_valid(light))
			continue;

		Light_data light_data = light->get_light_data();
		get_engine()->send_light_to_render(light_data);
	}

	for (Collision_component* box : m_collisions)
        get_engine()->send_collision_to_render(box->get_world_transform());

	Camera_data camera = get_camera_data();
	get_engine()->send_camera_to_render(camera);
}

void World::set_player_actor(Actor* player)
{
	m_player = player;
}

Camera_data World::get_camera_data()
{
	if (m_player && is_valid(m_player))
		return m_player->get_active_camera_data();
	else
	{
		m_player = nullptr;
		return Camera_data();
	}
}

void World::get_light_data(std::vector<Light_data>& out_data)
{
	std::vector<Light_component*> destroy;

	for (Light_component* light : m_lights)
	{
		if (light && is_valid(light))
			out_data.emplace_back(light->get_light_data());
		else
			destroy.emplace_back(light);
	}

	for (Light_component* light : destroy)
		m_lights.erase(light);
}

void World::add_UI_to_viewport(UI* ui)
{
	if (is_valid(ui))
	{
		m_viewport.insert(ui);
        ui->m_on_being_destroyed.add_object(this, &World::on_ui_destroyed);
		ui->on_added_to_viewport(this);
	}
}

void World::remove_UI_from_viewport(UI* ui)
{
	if (is_valid(ui))
    {
        ui->m_on_being_destroyed.remove_object(this);
        m_viewport.erase(ui);
	}
}

std::unordered_set<UI*>& World::get_viewport()
{
	return m_viewport; }

void World::on_actor_destroyed(Object* obj) 
{ 
	if (Actor* actor = dynamic_cast<Actor*>(obj))
    {
		m_actors.erase(actor);

		if (m_player == actor)
            m_player = nullptr;
    }
    else
		throw std::runtime_error("object was not actor");
}

void World::on_ui_destroyed(Object* obj) 
{ 
	remove_object_from_set(m_viewport, obj); 
}

void World::on_registered_light_destroyed(Object* obj) 
{
	remove_object_from_set(m_lights, obj);
}

void World::on_registered_mesh_destroyed(Object* obj) 
{ 
	remove_object_from_set(m_mesh_components, obj); 
}

void World::on_registered_collision_destroyed(Object* obj) 
{
    if (auto* collision = dynamic_cast<Collision_component*>(obj))
		m_collision_handler.unregister_component(collision);

    remove_object_from_set(m_collisions, obj);
}
