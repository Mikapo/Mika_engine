#pragma once

#include "Actor.h"
#include "Datatypes/Hit_result.h"
#include "Object.h"
#include "Utility/Collisions/Collision_handler.h"
#include <unordered_set>

namespace MEngine
{
    class Mesh_component;
    class Light_component;
    class Collision_component;
    class World : public Object
    {
        GENERATED_BODY(World)

    public:
        using Optional_collision = std::optional<Collision_result>;
        using Optional_hit_result = std::optional<Hit_result>;
        using Actor_ptr_set = std::unordered_set<Actor*>;

        // Is called every frame
        void update(float deltatime) override;

        // Spawns actor to the world
        Actor* spawn_actor(Class_obj* class_obj, Transform transform = Transform());

        void get_owned_objects(std::vector<Object*>& out_array) noexcept override;

        void register_mesh_component(Mesh_component* component);
        void register_light_component(Light_component* component);
        void register_collision_component(std::shared_ptr<Collider> collision, Collision_component* component);

        // Updates collision position
        void update_collisions(std::shared_ptr<Collider> collision, Collision_component* component);

        [[nodiscard]] Optional_collision find_collisions(
            const Collider* collision, Collision_component* component) const;
        [[nodiscard]] Optional_hit_result line_trace(Line line, const Actor_ptr_set& ignored_actors = Actor_ptr_set());

        // Gets data that is important for rendering this world
        void get_frame_data(Frame_data& out_frame_data);

        void set_player_actor(Actor* player) noexcept;

        template <typename T>
        [[nodiscard]] T* spawn_actor_cast(Class_obj* class_obj, Transform transform = Transform())
        {
            return dynamic_cast<T*>(spawn_actor(class_obj, transform));
        }

        template <typename T>
        [[nodiscard]] T* find_actor_of_class()
        {
            for (Actor* actor : m_actors)
                if (is_valid(actor))
                    if (T* actor_of_class = dynamic_cast<T*>(actor))
                        return actor_of_class;

            return nullptr;
        }

    private:
        [[nodiscard]] Camera_data get_camera_data();

        Collision_handler m_collision_handler;

        std::unordered_set<Actor*> m_actors;
        std::unordered_set<Mesh_component*> m_mesh_components;
        std::unordered_set<Light_component*> m_lights;
        std::unordered_set<Collision_component*> m_collisions;
        Actor* m_player = nullptr;
    };
} // namespace MEngine
