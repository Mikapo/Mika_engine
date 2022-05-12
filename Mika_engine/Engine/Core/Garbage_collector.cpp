#include "Garbage_collector.h"
#include "Objects/Object.h"


bool Garbage_collector::is_object_valid(Object* obj) const
{
    return m_registered_objects.contains(obj);
}

void Garbage_collector::register_object(Object* obj)
{
    m_registered_objects.insert(obj);
}

const std::unordered_set<Object*>& Garbage_collector::get_registered_objects() const
{
    return m_registered_objects;
}

void Garbage_collector::unregister_object(Object* obj)
{
    m_registered_objects.erase(obj);
}

void Garbage_collector::set_root_object(Object* obj)
{
    if (is_object_valid(obj))
        m_root = obj;
}

void Garbage_collector::mark_object_for_destruction(Object* obj)
{
    if (is_object_valid(obj))
        m_objects_to_destroy.push_back(obj);
}

void Garbage_collector::update()
{
    garbage_collect();
    finalize_destruction_on_objects();
}

void Garbage_collector::cleanup()
{
    if (m_registered_objects.size() == 0)
        return;

    for (Object* obj : m_registered_objects)
        if (!obj)
            m_registered_objects.erase(obj);
        else
            obj->destruct();

    finalize_destruction_on_objects();
}

void Garbage_collector::garbage_collect()
{
    check_object(m_root);
    destruct_unchecked_objects();
}

void Garbage_collector::check_object(Object* obj)
{
    if (!is_object_valid(obj) || obj->is_marked_by_garbage_collector())
        return;

    obj->set_garbage_collect_mark(true);
    std::vector<Object*> owned_objects;
    obj->get_owned_objects(owned_objects);

    for (Object* owned_object : owned_objects)
        check_object(owned_object); 
}

void Garbage_collector::destruct_unchecked_objects()
{
    if (m_registered_objects.size() == 0)
        return;

    for (Object* obj : m_registered_objects)
        if (!obj)
            m_registered_objects.erase(obj);
        else if (!obj->is_marked_by_garbage_collector())
            obj->destruct();
        else
            obj->set_garbage_collect_mark(false);
}

void Garbage_collector::finalize_destruction_on_objects()
{
    for (Object* obj : m_objects_to_destroy)
        if(is_object_valid(obj))
            obj->finalize_destruction();

    m_objects_to_destroy.clear();
}
