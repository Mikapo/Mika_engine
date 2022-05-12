#pragma once

#include "Object.h"
#include "Utility/Transform.h"
#include "Components/Actor_component.h"
#include "Utility/Frame_data.h"
#include "Rendering/Shading/Material.h"
#include "Utility/Delegate.h"
#include <unordered_set>

class Camera_component;
class World;
class Actor : public Object
{

public:
	void initialize() override;
	void update(float deltatime) override;
	void get_owned_objects(std::vector<Object*>& out_array) override;
	World* get_world() const;
	void set_world(World* world);
	void set_transform(Transform new_transform);
	void set_location(glm::vec3 new_location);
	void set_active_camera(Camera_component* camera);
	Transform get_transform() const;
	Camera_data get_active_camera_data();
	glm::vec3 get_forward_vector();
	glm::vec3 get_up_vector();
	void add_local_offset(glm::vec3 offset);
	void add_rotation_offset(Rotator rotation);

	template<typename T>
	T* create_component()
	{
		T* component = Object::construct_object<T>(get_engine());
		Actor_component* default_component = component;
		default_component->set_owner(this);
		default_component->set_world(get_world());
		m_components.insert(default_component);
		default_component->initialize();
		return component;
	}

	template<typename T>
	T* find_component_by_class()
	{
		for (Actor_component* component : m_components)
			if (T* found_component = dynamic_cast<T*>(component))
				return found_component;

		return nullptr;
	}

	Delegate<Actor*> m_on_transform_change;

private:
	void update_local_coordinate_system();

	std::unordered_set<Actor_component*> m_components;
	Camera_component* m_active_camera = nullptr;
	World* m_owning_world = nullptr;

	Transform m_transform;
	Coordinate_system m_local_coordinate_system;
};

