#pragma once

#include "Datatypes/Transform.h"
#include "Collision.h"
#include <array>


class Oriented_bounding_box : public Collision
{
public:
    Oriented_bounding_box(Transform transform = Transform());

    void update(Transform transform) override; 
    glm::mat4 get_model() const;
    Axis_comparison_result compare_to_axis(glm::vec3 axis_origin, Axis axis) const override;
    bool is_overlapping(const Collision* other) const override;
    std::optional<Hit_result> is_overlapping_with_line(const Line& line) const override;
    bool is_overlapping_with_obb(const Oriented_bounding_box* other) const override;
    const std::array<glm::vec3, 8>& get_vertices() const;
    const std::array<glm::vec3, 3>& get_normals() const;
    
private:
    glm::mat4 m_model;
    glm::vec3 m_extend;
    std::array<glm::vec3, 3> m_normals = {};
    std::array<glm::vec3, 8> m_vertices = {};
    const static std::array<glm::vec3, 8> m_box_vertices;
};
