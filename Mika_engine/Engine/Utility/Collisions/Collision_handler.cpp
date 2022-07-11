#include "Collision_handler.h"
#include <stdexcept>

void Collision_handler::unregister_component(const Collision_component* component) noexcept
{
    m_colliders.erase(const_cast<Collision_component*>(component));
}

void Collision_handler::update_component(Collision_component* component, std::shared_ptr<Collider> collider)
{
    auto found_collider = m_colliders.find(component);

    if (found_collider != m_colliders.end())
        found_collider->second = collider;
    else
        m_colliders.emplace(component, collider);
}

std::optional<Collision_result> Collision_handler::find_collisions(
    const Collider* collider, Collision_component* component) const
{
    if (!collider)
        return std::optional<Collision_result>();

    for (auto& collider_to_check : m_colliders)
    {
        if (collider_to_check.first == component)
            continue;

        auto result = collider->is_overlapping(collider_to_check.second.get());

        if (result.has_value())
        {
            result.value().m_this_component = component;
            result.value().m_other_component = collider_to_check.first;
            return result;
        }
    }

    return std::optional<Collision_result>();
}

std::optional<Hit_result> Collision_handler::find_overlaps_with_line(
    const Line* line, const std::unordered_set<Actor*>& ignored_actors)
{
    if (!line)
        throw std::invalid_argument("line is null");

    for (auto& collider_to_check : m_colliders)
    {
        auto result = collider_to_check.second->is_overlapping_with_line(*line);

        if (result.has_value())
            return result;
    }

    return std::optional<Hit_result>();
}
