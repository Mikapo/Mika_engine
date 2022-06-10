#pragma once

#include "Datatypes/Transform.h"
#include "Datatypes/Axis.h"
#include "Datatypes/Hit_result.h"
#include "Datatypes/Axis_comparison_result.h"
#include "glm/vec3.hpp"
#include <optional>


struct Line;
class Oriented_bounding_box;
class Collision
{
public:
    glm::vec3 get_origin() const;
    virtual Axis_comparison_result compare_to_axis(glm::vec3 axis_origin, Axis axis) const = 0;
    virtual void update(Transform transform);
    virtual bool is_overlapping(const Collision* collision) const = 0;
    virtual std::optional<Hit_result> is_overlapping_with_line(const Line& line) const = 0;
    virtual bool is_overlapping_with_obb(const Oriented_bounding_box* collision) const = 0;

protected:
    glm::vec3 m_origin;
};
