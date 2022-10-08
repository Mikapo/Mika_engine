#include "Object.h"
#include "Core/Engine.h"
#include <string>

namespace MEngine
{
    void Object::destruct() noexcept
    {
        m_marked_for_destruction = true;
        DEBUG_LOG(notification, objects, "{} is going to be destroyed", get_class_name());
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

    Engine* Object::get_engine() noexcept
    {
        return m_engine;
    }

    const Engine* Object::get_engine() const noexcept
    {
        return m_engine;
    }

    void Object::update(float deltatime)
    {
        if (m_lifetime_has_been_set)
        {
            using namespace std::chrono;
            const auto time_since_lifetime_has_been_set =
                high_resolution_clock::now() - m_time_since_lifetime_has_been_set;

            if (time_since_lifetime_has_been_set.count() * 0.000000001f > m_lifetime)
                destruct();
        }
    }

    std::string_view Object::get_class_name()
    {
        return get_class()->get_name();
    }

    bool Object::is_valid(const Object* obj) const
    {
        return static_is_valid(get_engine(), obj);
    }

    bool Object::static_is_valid(const Engine* engine, const Object* obj)
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

    void Object::register_object(Engine* engine, std::unique_ptr<Object> obj)
    {
        if (!engine)
            throw std::invalid_argument("engine was null");

        if (!obj)
            throw std::invalid_argument("obj was null");

        engine->register_object(std::move(obj));
    }

    void Object::set_engine(Engine* engine) noexcept
    {
        m_engine = engine;
    }

    size_t Object::get_amount_of_registered_objects() noexcept
    {
        return get_engine()->get_amount_of_registered_objects();
    }

} // namespace MEngine
