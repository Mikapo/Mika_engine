#include "World.h"

#include "Components/Scene_components/Mesh_component.h"
#include "Components/Scene_components/Light_component.h"


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

void World::register_mesh_component(Mesh_component* component)
{
	m_mesh_components.insert(component);
}

void World::register_light_component(Light_component* component)
{
	m_lights.insert(component);
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
		ui->on_added_to_viewport(this);
	}
}

void World::remove_UI_from_viewport(UI* ui)
{
	if (is_valid(ui))
		m_viewport.erase(ui);
}

std::unordered_set<UI*>& World::get_viewport()
{
	return m_viewport;
}
