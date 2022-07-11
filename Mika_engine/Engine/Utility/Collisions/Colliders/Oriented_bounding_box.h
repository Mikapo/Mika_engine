#pragma once

#include "Collider.h"
#include "Datatypes/Transform.h"
#include <array>

class Oriented_bounding_box : public Collider
{
public:
    Oriented_bounding_box(Transform transform = Transform()) noexcept;

    void update(Transform transform) override;
    std::optional<Collision_result> is_overlapping(const Collider* collider) const override;
    std::optional<Hit_result> is_overlapping_with_line(const Line& line) const override;
    std::optional<Collision_result> is_overlapping_with_obb(const Oriented_bounding_box& collider) const override;
    std::optional<Collision_result> is_overlapping_with_sphere(const Sphere& collider) const override;
    const std::array<glm::vec3, 8>& get_vertices() const noexcept;
    const std::array<glm::vec3, 3>& get_normals() const noexcept;

private:
    std::array<glm::vec3, 3> m_normals = {};
    std::array<glm::vec3, 8> m_vertices = {};
    const static std::array<glm::vec3, 8> m_box_vertices;
};
