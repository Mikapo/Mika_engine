#pragma once

#include "Colliders/Collider.h"
#include "Datatypes/Axis.h"
#include "Datatypes/Hit_result.h"
#include <memory>
#include <optional>
#include <unordered_map>
#include <unordered_set>

namespace Mika_engine
{
    class Collision_component;
    class Actor;
    struct Line;
    class Collision_handler
    {
    public:
        void unregister_component(const Collision_component* component) noexcept;
        void update_component(Collision_component* component, std::shared_ptr<Collider> collider);
        std::optional<Collision_result> find_collisions(const Collider* collider, Collision_component* component) const;
        std::optional<Hit_result> find_overlaps_with_line(
            const Line* line, const std::unordered_set<Actor*>& ignored_actors);

    private:
        std::unordered_map<Collision_component*, std::shared_ptr<Collider>> m_colliders;
    };

}
