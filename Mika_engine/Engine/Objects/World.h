#pragma once

#include "Actor.h"
#include "Datatypes/Hit_result.h"
#include "Object.h"
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
    void get_owned_objects(std::vector<Object*>& out_array) noexcept override;
    Actor* spawn_actor(Class_obj* class_obj, Transform transform = Transform());
    UI* create_ui(Class_obj* class_obj);
    void register_mesh_component(Mesh_component* component);
    void register_light_component(Light_component* component);
    void register_collision_component(std::shared_ptr<Collider> collision, Collision_component* component);
    void update_collisions(const std::shared_ptr<Collider> collision, Collision_component* component);
    std::optional<Collision_result> find_collisions(const Collider* collision, Collision_component* component) const;
    std::optional<Hit_result> line_trace(
        glm::vec3 start, glm::vec3 end,
        const std::unordered_set<Actor*>& ignored_actors = std::unordered_set<Actor*>());
    void get_frame_data(Frame_data& out_frame_data);
    void set_player_actor(Actor* player) noexcept;
    void add_UI_to_viewport(UI* ui);
    void remove_UI_from_viewport(UI* ui);
    std::unordered_set<UI*>& get_viewport() noexcept;

    template <typename T>
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
    Camera_data get_camera_data();

    std::unordered_set<Actor*> m_actors;
    std::unordered_set<UI*> m_viewport;
    std::unordered_set<Mesh_component*> m_mesh_components;
    std::unordered_set<Light_component*> m_lights;
    std::unordered_set<Collision_component*> m_collisions;
    Actor* m_player = nullptr;
    Collision_handler m_collision_handler;
};
