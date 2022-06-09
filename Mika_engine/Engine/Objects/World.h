#pragma once

#include "Object.h"
#include "Actor.h"
#include "Utility/Collisions/Collision_handler.h"
#include <unordered_set>

class Shader;
class Mesh_component;
class Light_component;
class Collision_component;
class UI;
class World : public Object
{
    GENERATED_BODY(World)

public:
	void update(float deltatime) override;
	void get_owned_objects(std::vector<Object*>& out_array) override;
    Actor* spawn_actor(Class_obj* class_obj, Transform transform = Transform());
    UI* create_ui(Class_obj* class_obj);
	void register_mesh_component(Mesh_component* component);
	void register_light_component(Light_component* component);
    void register_collision_component(std::shared_ptr<Collision> collision, Collision_component* component);
    void update_collisions(std::shared_ptr<Collision> collision, Collision_component* component);
    std::optional<Collision_component*> find_collisions(
        Collision* collision, const Collision_component* component) const;
	void send_data_to_render();
	void set_player_actor(Actor* player);
	void add_UI_to_viewport(UI* ui);
	void remove_UI_from_viewport(UI* ui);
	std::unordered_set<UI*>& get_viewport();

    template<typename T>
    T* spawn_actor_cast(Class_obj* class_obj, Transform transform = Transform())
    {
        return dynamic_cast<T*>(spawn_actor(class_obj, transform));
    }

    template <typename T>
    T* find_actor_of_class()
    {
        for (Actor* actor : m_actors)
            if (is_valid(actor))
                if (T* actor_of_class = dynamic_cast<T*>(actor))
                    return actor_of_class;

        return nullptr;
    }	

private:
    void on_actor_destroyed(Object* obj);
    void on_ui_destroyed(Object* obj);
    void on_registered_light_destroyed(Object* obj);
    void on_registered_mesh_destroyed(Object* obj);
    void on_registered_collision_destroyed(Object* obj);
    Camera_data get_camera_data();
    void get_light_data(std::vector<Light_data>& out_data);

	std::unordered_set<Actor*> m_actors;
	std::unordered_set<UI*> m_viewport;
	std::unordered_set<Mesh_component*> m_mesh_components;
	std::unordered_set<Light_component*> m_lights;
    std::unordered_set<Collision_component*> m_collisions;
	Actor* m_player = nullptr;
    Collision_handler m_collision_handler;
};

