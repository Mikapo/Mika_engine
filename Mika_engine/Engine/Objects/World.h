#pragma once

#include "Object.h"
#include "Actor.h"
#include "UI/UI.h"

#include <unordered_set>

class Shader;
class Mesh_component;
class Light_component;
class World : public Object
{
public:
	template<typename T>
	T* find_actor_of_class()
	{
		for (Actor* actor : m_actors)
			if (T* actor_of_class = dynamic_cast<T*>(actor))
				return actor_of_class;

		return nullptr;
	}

	template<typename T>
	T* spawn_actor()
	{
		T* obj_ptr = Object::construct_object<T>(get_engine());
		Actor* default_actor = obj_ptr;
		default_actor->set_world(this);
		m_actors.insert(default_actor);
		default_actor->initialize();
		return obj_ptr;
	}

	template<typename T>
	T* create_ui()
	{
		T* obj_ptr = Object::construct_object<T>(get_engine());
		UI* default_ui = obj_ptr;
		default_ui->initialize();
		return obj_ptr;
	}

	void update(float deltatime) override;
	void get_owned_objects(std::vector<Object*>& out_array) override;
	void register_mesh_component(Mesh_component* component);
	void register_light_component(Light_component* component);
	void send_data_to_render();
	void set_player_actor(Actor* player);
	Camera_data get_camera_data();
	void get_light_data(std::vector<Light_data>& out_data);
	void add_UI_to_viewport(UI* ui);
	void remove_UI_from_viewport(UI* ui);
	std::unordered_set<UI*>& get_viewport();

private:
	std::unordered_set<Actor*> m_actors;
	std::unordered_set<UI*> m_viewport;
	std::unordered_set<Mesh_component*> m_mesh_components;
	std::unordered_set<Light_component*> m_lights;
	Actor* m_player = nullptr;
};

