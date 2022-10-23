#include "World.h"

#include "Components/Scene_components/Collision_component.h"
#include "Components/Scene_components/Light_component.h"
#include "Components/Scene_components/Mesh_component.h"
#include "Core/Engine.h"
#include "Utility/Collisions/Line.h"

namespace MEngine
{
    void World::update(float deltatime)
    {
        Object::update(deltatime);

        update_owned_objects(m_actors, deltatime);
    }

    void World::get_owned_objects(std::vector<Object*>& out_array) noexcept
    {
        Object::get_owned_objects(out_array);

        for (Actor* actor : m_actors)
            out_array.push_back(actor);
    }

    Actor* World::spawn_actor(Class_obj* class_obj, Transform transform)
    {
        if (!class_obj)
            throw std::invalid_argument("class_obj is null");

        Actor* actor = class_obj->construct_cast<Actor>(get_engine());
        if (!actor)
            return nullptr;

        m_actors.insert(actor);
        actor->set_world(this);
        actor->set_transform(transform);
        actor->initialize();
        return actor;
    }

    void World::register_mesh_component(Mesh_component* component)
    {
        m_mesh_components.insert(component);
    }

    void World::register_light_component(Light_component* component)
    {
        m_lights.insert(component);
    }

    void World::register_collision_component(std::shared_ptr<Collider> collision, Collision_component* component)
    {
        if (!component)
            throw std::invalid_argument("component is null");

        m_collisions.insert(component);
        m_collision_handler.update_component(component, collision);
    }

    void World::update_collisions(const std::shared_ptr<Collider> collision, Collision_component* component)
    {
        if (!component)
            throw std::invalid_argument("component is null");

        m_collision_handler.update_component(component, collision);
    }

    World::Optional_collision World::find_collisions(const Collider* collision, Collision_component* component) const
    {
        if (!collision)
            throw std::invalid_argument("collision is null");

        if (!component)
            throw std::invalid_argument("component is null");

        return m_collision_handler.find_collisions(collision, component);
    }

    World::Optional_hit_result World::line_trace(Line line, const Actor_ptr_set& ignored_actors)
    {
        return m_collision_handler.find_overlaps_with_line(&line, ignored_actors);
    }

    void World::get_frame_data(Frame_data& out_frame_data)
    {
        out_frame_data.m_meshes.reserve(m_mesh_components.size());

        auto mesh_it = m_mesh_components.begin();
        while (mesh_it != m_mesh_components.end())
        {
            if (!is_valid(*mesh_it))
            {
                mesh_it = m_mesh_components.erase(mesh_it);
                continue;
            }

            auto mesh_data = (*mesh_it)->get_mesh_data();

            if (mesh_data.has_value())
                out_frame_data.m_meshes.emplace_back(mesh_data.value());

            ++mesh_it;
        }

        out_frame_data.m_lighting.reserve(m_lights.size());

        auto light_it = m_lights.begin();
        while (light_it != m_lights.end())
        {
            if (!is_valid(*light_it))
            {
                light_it = m_lights.erase(light_it);
                continue;
            }

            out_frame_data.m_lighting.emplace_back((*light_it)->get_light_data());
            ++light_it;
        }

        out_frame_data.m_camera = get_camera_data();
    }

    void World::set_player_actor(Actor* player) noexcept
    {
        m_player = player;
    }

    Camera_data World::get_camera_data()
    {
        if (m_player && is_valid(m_player))
            return m_player->get_active_camera_data();
        else
        {
            m_player = nullptr;
            return Camera_data();
        }
    }
} // namespace MEngine
