#pragma once

#include "../Actor_component.h"
#include "Datatypes/Transform.h"

namespace MEngine
{
    class Scene_component : public Actor_component
    {
        GENERATED_BODY(Scene_component)

    public:
        // Gets called when created
        void initialize() override;

        void set_relative_transform(Transform transform);
        void set_relative_location(glm::vec3 new_location);
        void set_relative_rotation(Rotator new_rotation);
        void set_relative_scale(glm::vec3 new_scale);

        [[nodiscard]] Transform get_relative_transform() const noexcept;
        [[nodiscard]] Transform get_world_transform() const noexcept;

        [[nodiscard]] glm::vec3 get_relative_forward_vector() const noexcept;
        [[nodiscard]] glm::vec3 get_relative_up_vector() const noexcept;

    protected:
        [[nodiscard]] Transform calculate_component_world_transform(Transform owner_transform);
        virtual void update_world_transform();

    private:
        void update_directional_vectors();

        // Event that gets called when owner transform changes
        void on_owner_transform_change(Actor* owner);

        Transform m_relative_transform;
        Transform m_world_transform;
        Directional_vectors m_local_directional_vectors;
    };
} // namespace MEngine
