#pragma once

#include "Object.h"
#include "Datatypes/Transform.h"
#include "Components/Actor_component.h"
#include "Datatypes/Frame_data.h"
#include "Rendering/Shading/Material.h"
#include "Utility/Delegate.h"
#include <unordered_set>

class Collision_component;
class Camera_component;
class World;
class Actor : public Object
{
    GENERATED_BODY(Actor)

public:
	void initialize() override;
	void update(float deltatime) override;
	void get_owned_objects(std::vector<Object*>& out_array) override;
	World* get_world() const;
	void set_world(World* world);
    void set_transform(Transform new_transform, bool check_for_collision = false);
    void set_location(glm::vec3 new_location, bool check_for_collision = false);
    void set_rotation(Rotator new_rotation, bool check_for_collision = false);
    void set_scale(glm::vec3 new_scale, bool check_for_collision = false);
    glm::vec3 get_location() const;
    Rotator get_rotation() const;
    glm::vec3 get_scale() const;
	void set_active_camera(Camera_component* camera);
	Transform get_transform() const;
	Camera_data get_active_camera_data();
	glm::vec3 get_forward_vector();
	glm::vec3 get_up_vector();
    void add_local_offset(glm::vec3 offset, bool check_for_collision = false);
    void add_world_offset(glm::vec3 offset, bool check_for_collision = false);
    void add_rotation_offset(Rotator rotation, bool check_for_collision = false);
    bool check_collisions(std::optional<Transform> transform);
    Actor_component* create_component(Class_obj* class_obj);

	template <typename T>
	T* create_component_cast(Class_obj* class_obj)
	{
        return dynamic_cast<T*>(create_component(class_obj));
	}

	template<typename T>
	T* find_component_by_class()
	{
		for (Actor_component* component : m_components)
			if (T* found_component = dynamic_cast<T*>(component))
                if (is_valid(found_component))
				return found_component;

		return nullptr;
	}

	Delegate<Actor*> m_on_transform_change;
    Delegate<Collision_component*, Collision_component*> m_on_collision_detected;

private:
	void update_local_coordinate_system();
    void on_component_destroyed(Object* component);
    void on_collision_component_destroyed(Object* collision);
    void on_active_camera_being_destroyed(Object* camera);

	std::unordered_set<Actor_component*> m_components;
    std::unordered_set<Collision_component*> m_collisions;
	Camera_component* m_active_camera = nullptr;
	World* m_owning_world = nullptr;

	Transform m_transform;
	Directional_vectors m_directional_vectors;
};

