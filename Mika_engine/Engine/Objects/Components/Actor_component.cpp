#include "Actor_component.h"

namespace Mika_engine
{
    void Actor_component::set_owner(Actor* owner) noexcept
    {
        m_owning_actor = owner;
    }

    Actor* Actor_component::get_owner() const noexcept
    {
        return m_owning_actor;
    }

    void Actor_component::set_world(World* world) noexcept
    {
        m_owning_world = world;
    }

    World* Actor_component::get_world() const noexcept
    {
        return m_owning_world;
    }
} // namespace Mika_engine
