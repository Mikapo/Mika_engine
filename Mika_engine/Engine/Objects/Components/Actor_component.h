#pragma once

#include "../Object.h"
#include "Datatypes/Transform.h"

namespace MEngine
{
    class Actor;
    class World;
    class Actor_component : public Object
    {
        GENERATED_BODY(Actor_component)

    public:
        void set_owner(Actor* owner) noexcept;
        Actor* get_owner() const noexcept;
        void set_world(World* world) noexcept;
        World* get_world() const noexcept;

    private:
        World* m_owning_world = nullptr;
        Actor* m_owning_actor = nullptr;
    };
} // namespace MEngine
