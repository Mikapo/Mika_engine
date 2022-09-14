#pragma once

#include "Datatypes/Min_max.h"
#include "Scene_component.h"
#include "Utility/Collisions/Colliders/Collider.h"
#include <cstdint>
#include <memory>
#include <optional>

namespace Mika_engine
{
    enum class Collider_type : uint8_t
    {
        obb,
        sphere
    };

    class Collision_component : public Scene_component
    {
        GENERATED_BODY(Collision_component)

    public:
        Collision_component() noexcept;
        void set_collider_type(Collider_type type);
        void initialize() override;
        bool is_overlapping(const Collision_component* other) const;
        std::optional<Hit_result> is_overlapping_with_line(const Line& line) const;
        bool check_for_collisions();
        Collision_result get_previous_collision() const noexcept;

    private:
        void update_world_transform() override;

        Collider_type m_current_collider_type = Collider_type::obb;
        std::shared_ptr<Collider> m_collider = nullptr;
        Collision_result m_previous_collision;
    };
} // namespace Mika_engine
