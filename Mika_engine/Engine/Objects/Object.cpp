#include "Object.h"
#include "Core/Mika_engine.h"
#include <string>

void Object::destruct()
{
    m_marked_for_destruction = true;
    m_on_being_destroyed.broadcast(this);
    LOG(notification, objects, "Object with name {} destroyed", get_class_name());
}

void Object::set_garbage_collect_mark(bool mark) noexcept
{
    m_garbage_collector_mark = mark;
}

bool Object::is_marked_by_garbage_collector() const noexcept
{
    return m_garbage_collector_mark;
}

bool Object::is_marked_for_destruction() const noexcept
{
    return m_marked_for_destruction;
}

Mika_engine* Object::get_engine() noexcept
{
    return m_engine;
}

Asset_manager& Object::get_asset_manager() noexcept
{
    return get_engine()->get_asset_manager();
}

const Mika_engine* Object::get_engine() const noexcept
{
    return m_engine;
}

void Object::update(float deltatime)
{
    if (m_lifetime_has_been_set)
    {
        using namespace std::chrono;
        const auto time_since_lifetime_has_been_set = high_resolution_clock::now() - m_time_since_lifetime_has_been_set;

        if (time_since_lifetime_has_been_set.count() * 0.000000001f > m_lifetime)
            destruct();
    }
}

std::string Object::get_class_name()
{
    return std::string(typeid(*this).name()).substr(6);
}

bool Object::is_valid(const Object* obj) const
{
    return static_is_valid(get_engine(), obj);
}

bool Object::static_is_valid(const Mika_engine* engine, const Object* obj)
{
    if (!engine)
        throw std::invalid_argument("engine was null");

    return engine->is_object_valid(obj);
}

void Object::set_lifetime(float lifetime) noexcept
{
    m_lifetime_has_been_set = true;
    m_time_since_lifetime_has_been_set = std::chrono::high_resolution_clock::now();
    m_lifetime = lifetime;
}

void Object::register_object(Mika_engine* engine, std::unique_ptr<Object> obj)
{
    if (!engine)
        throw std::invalid_argument("engine was null");

    if (!obj)
        throw std::invalid_argument("obj was null");

    engine->register_object(std::move(obj));
}

void Object::set_engine(Mika_engine* engine) noexcept
{
    m_engine = engine;
}

size_t Object::get_amount_of_registered_objects() noexcept
{
    return get_engine()->get_amount_of_registered_objects();
}
