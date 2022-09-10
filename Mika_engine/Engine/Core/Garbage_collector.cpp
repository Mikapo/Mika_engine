#include "Garbage_collector.h"
#include "Objects/Object.h"

bool Garbage_collector::is_object_valid(const Object* obj) const
{
    return m_registered_objects.contains(const_cast<Object*>(obj));
}

void Garbage_collector::register_object(std::unique_ptr<Object> obj)
{
    m_registered_objects.emplace(obj.get(), std::move(obj));
}

const std::unordered_map<Object*, std::unique_ptr<Object>>& Garbage_collector::get_registered_objects() const noexcept
{
    return m_registered_objects;
}

void Garbage_collector::set_root_object(Object* obj)
{
    if (is_object_valid(obj))
        m_root = obj;
}

void Garbage_collector::update()
{
    finalize_destruction_on_objects();
    garbage_collect();
}

void Garbage_collector::cleanup()
{
    if (m_registered_objects.size() == 0)
        return;

    for (auto& obj_pair : m_registered_objects)
    {
        Object* obj = obj_pair.first;

        if (!obj)
            m_registered_objects.erase(obj);
        else
            obj->destruct();
    }

    finalize_destruction_on_objects();
}

void Garbage_collector::garbage_collect()
{
    check_object(m_root);
    destruct_unchecked_objects();
}

void Garbage_collector::check_object(Object* obj)
{
    if (!obj || !is_object_valid(obj) || obj->is_marked_by_garbage_collector())
        return;

    obj->set_garbage_collect_mark(true);
    std::vector<Object*> owned_objects;
    obj->get_owned_objects(owned_objects);

    for (Object* obj : owned_objects)
        check_object(obj);
}

void Garbage_collector::destruct_unchecked_objects()
{
    if (m_registered_objects.size() == 0)
        return;

    for (auto& obj_pair : m_registered_objects)
    {
        Object* obj = obj_pair.first;

        if (!obj)
            m_registered_objects.erase(obj);
        else if (!obj->is_marked_by_garbage_collector())
            obj->destruct();
        else
            obj->set_garbage_collect_mark(false);
    }
}

void Garbage_collector::finalize_destruction_on_objects()
{
    static std::vector<Object*> objects_to_destroy;

    for (auto& obj : m_registered_objects)
        if (is_object_valid(obj.first) && obj.first->is_marked_for_destruction())
        {
            LOG(notification, garbage_collector, "Object {} is being garbage collected", obj.first->get_class_name());
            objects_to_destroy.emplace_back(obj.first);
        }

    for (Object* obj : objects_to_destroy)
        m_registered_objects.erase(obj);
}
