#include "World.h"

#include "Components/Scene_components/Collision_component.h"
#include "Components/Scene_components/Light_component.h"
#include "Components/Scene_components/Mesh_component.h"
#include "Core/Mika_engine.h"
#include "Objects/UI/UI.h"
#include "Utility/Collisions/Line.h"

void World::update(float deltatime)
{
    Object::update(deltatime);

    update_owned_objects(m_actors, deltatime);
    update_owned_objects(m_viewport, deltatime);
}

void World::get_owned_objects(std::vector<Object*>& out_array) noexcept
{
    Object::get_owned_objects(out_array);

    for (Actor* actor : m_actors)
        out_array.push_back(actor);

    for (UI* ui : m_viewport)
        out_array.push_back(ui);
}

Actor* World::spawn_actor(Class_obj* class_obj, Transform transform)
{
    if (!class_obj)
        throw std::invalid_argument("class_obj is null");

    Actor* actor = class_obj->construct_cast<Actor>(get_engine());
    if (!actor)
        return nullptr;

    m_actors.insert(actor);
    actor->m_on_being_destroyed.add_object(this, &World::on_actor_destroyed);
    actor->set_world(this);
    actor->set_transform(transform);
    actor->initialize();
    return actor;
}

UI* World::create_ui(Class_obj* class_obj)
{
    if (!class_obj)
        throw std::invalid_argument("class_obj is null");

    UI* ui = class_obj->construct_cast<UI>(get_engine());
    if (!ui)
        return nullptr;

    return ui;
}

void World::register_mesh_component(Mesh_component* component)
{
    m_mesh_components.insert(component);
    component->m_on_being_destroyed.add_object(this, &World::on_registered_mesh_destroyed);
}

void World::register_light_component(Light_component* component)
{
    m_lights.insert(component);
    component->m_on_being_destroyed.add_object(this, &World::on_registered_light_destroyed);
}

void World::register_collision_component(std::shared_ptr<Collider> collision, Collision_component* component)
{
    if (!component)
        throw std::invalid_argument("component is null");

    m_collisions.insert(component);
    m_collision_handler.update_component(component, collision);
    component->m_on_being_destroyed.add_object(this, &World::on_registered_collision_destroyed);
}

void World::update_collisions(const std::shared_ptr<Collider> collision, Collision_component* component)
{
    if (!component)
        throw std::invalid_argument("component is null");

    m_collision_handler.update_component(component, collision);
}

std::optional<Collision_result> World::find_collisions(const Collider* collision, Collision_component* component) const
{
    if (!collision)
        throw std::invalid_argument("collision is null");

    if (!component)
        throw std::invalid_argument("component is null");

    return m_collision_handler.find_collisions(collision, component);
}

std::optional<Hit_result> World::line_trace(
    glm::vec3 start, glm::vec3 end, const std::unordered_set<Actor*>& ignored_actors)
{
    Line line = {.m_start = start, .m_end = end};
    return m_collision_handler.find_overlaps_with_line(&line, ignored_actors);
}

void World::get_frame_data(Frame_data& out_frame_data)
{
    out_frame_data.m_meshes.reserve(m_mesh_components.size());

    for (const Mesh_component* component : m_mesh_components)
    {
        if (!component)
            continue;

        auto mesh_data = component->get_mesh_data();

        if (mesh_data.has_value())
            out_frame_data.m_meshes.emplace_back(mesh_data.value());
    }

    out_frame_data.m_lighting.reserve(m_lights.size());

    for (const Light_component* component : m_lights)
        if (component)
            out_frame_data.m_lighting.emplace_back(component->get_light_data());

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

void World::add_UI_to_viewport(UI* ui)
{
    if (!ui)
        throw std::invalid_argument("ui is null");

    if (is_valid(ui))
    {
        m_viewport.insert(ui);
        ui->m_on_being_destroyed.add_object(this, &World::on_ui_destroyed);
        ui->on_added_to_viewport.broadcast(this);
    }
}

void World::remove_UI_from_viewport(UI* ui)
{
    if (!ui)
        throw std::invalid_argument("ui is null");

    if (is_valid(ui))
    {
        ui->m_on_being_destroyed.remove_object(this);
        m_viewport.erase(ui);
    }
}

std::unordered_set<UI*>& World::get_viewport() noexcept
{
    return m_viewport;
}

void World::on_actor_destroyed(Object* obj)
{
    if (Actor* actor = dynamic_cast<Actor*>(obj))
    {
        m_actors.erase(actor);

        if (m_player == actor)
            m_player = nullptr;
    }
    else
        throw std::runtime_error("object was not actor");
}

void World::on_ui_destroyed(Object* obj)
{
    remove_object_from_set(m_viewport, obj);
}

void World::on_registered_light_destroyed(Object* obj)
{
    remove_object_from_set(m_lights, obj);
}

void World::on_registered_mesh_destroyed(Object* obj)
{
    remove_object_from_set(m_mesh_components, obj);
}

void World::on_registered_collision_destroyed(Object* obj)
{
    if (const auto* const collision = dynamic_cast<Collision_component*>(obj))
        m_collision_handler.unregister_component(collision);

    remove_object_from_set(m_collisions, obj);
}
