#pragma once

#include "Components/Actor_component.h"
#include "Datatypes/Collision_result.h"
#include "Datatypes/Frame_data.h"
#include "Datatypes/Transform.h"
#include "Object.h"
#include "Utility/Delegate.h"
#include <unordered_set>

namespace MEngine
{
    class Collision_component;
    class Camera_component;
    class World;

    // Represents object that has position and can have components
    class Actor : public Object
    {
        GENERATED_BODY(Actor)

    public:
        Actor() = default;

        // Gets called when Actor is created
        void initialize() override;

        // Gets called on every frame
        void update(float deltatime) override;

        void get_owned_objects(std::vector<Object*>& out_array) noexcept override;
        void destruct() noexcept override;

        [[nodiscard]] World* get_world() const noexcept;
        void set_world(World* world) noexcept;

        void set_transform(Transform new_transform, bool check_for_collision = false);
        void set_location(glm::vec3 new_location, bool check_for_collision = false);
        void set_rotation(Rotator new_rotation, bool check_for_collision = false);
        void set_scale(glm::vec3 new_scale, bool check_for_collision = false);

        [[nodiscard]] Transform get_transform() const noexcept;
        [[nodiscard]] glm::vec3 get_location() const noexcept;
        [[nodiscard]] Rotator get_rotation() const noexcept;
        [[nodiscard]] glm::vec3 get_scale() const noexcept;

        [[nodiscard]] glm::vec3 get_forward_vector() const noexcept;
        [[nodiscard]] glm::vec3 get_up_vector() const noexcept;
        [[nodiscard]] glm::vec3 get_right_vector() const noexcept;

        void add_local_offset(glm::vec3 offset, bool check_for_collision = false);
        void add_world_offset(glm::vec3 offset, bool check_for_collision = false);
        void add_rotation_offset(Rotator rotation, bool check_for_collision = false);

        void set_active_camera(Camera_component* camera);
        [[nodiscard]] Camera_data get_active_camera_data();

        void register_collision(Collision_component* collision) noexcept;

        /**
         * Checks if this actor collides with anything currently
         * and broadcasts m_on_collision_detected delegate if there is collision
         */
        [[nodiscard]] bool check_collisions();

        Actor_component* create_component(Class_obj* class_obj);

        template <typename T>
        [[nodiscard]] T* create_component_cast(Class_obj* class_obj)
        {
            return dynamic_cast<T*>(create_component(class_obj));
        }

        template <typename T>
        [[nodiscard]] T* find_component_by_class()
        {
            for (Actor_component* component : m_components)
                if (T* found_component = dynamic_cast<T*>(component))
                    if (is_valid(found_component))
                        return found_component;

            return nullptr;
        }

        Delegate<Actor*> m_on_transform_change;
        Delegate<Collision_result> m_on_collision_detected;

    private:
        // updated m_directional_vectors with current transform
        void update_directional_vectors();

        std::unordered_set<Actor_component*> m_components;
        std::unordered_set<Collision_component*> m_collisions;
        Camera_component* m_active_camera = nullptr;
        World* m_owning_world = nullptr;

        Transform m_transform;
        Directional_vectors m_directional_vectors;
    };
} // namespace MEngine
