#pragma once

#include "Scene_component.h"
#include "Utility/Collisions/Collision.h"
#include "Datatypes/Min_max.h"
#include <optional>
#include <memory>

class Collision_component : public Scene_component
{
    GENERATED_BODY(Collision_component)

public:
    Collision_component();
    void initialize() override;
    bool is_overlapping(Collision_component* other) const;
    bool is_overlapping_with_line(const Line& line) const;
    std::optional<Collision_component*> check_for_collisions(
        std::optional<Transform> owner_transform = std::optional<Transform>());

private:
    void update_world_transform() override;

    std::shared_ptr<Collision> m_collision;
};
