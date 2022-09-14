#pragma once

#include "Collider.h"

namespace Mika_engine
{
    class Sphere : public Collider
    {
    public:
        float get_radius() const noexcept;
        void update(Transform transform) override;
        std::optional<Collision_result> is_overlapping(const Collider* collider) const override;
        std::optional<Hit_result> is_overlapping_with_line(const Line& line) const override;
        std::optional<Collision_result> is_overlapping_with_obb(const Oriented_bounding_box& collider) const override;
        std::optional<Collision_result> is_overlapping_with_sphere(const Sphere& collider) const override;

    private:
        float m_radius = 0.0f;
    };
} // namespace Mika_engine
