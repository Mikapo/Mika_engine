#include "Garbage_collector.h"
#include "Objects/Object.h"

namespace MEngine
{
    bool Garbage_collector::is_object_valid(const Object* obj) const
    {
        if (obj == nullptr)
            return false;

        return m_registered_objects.contains(obj);
    }

    void Garbage_collector::register_object(std::unique_ptr<Object> obj)
    {
        m_registered_objects.emplace(obj.get(), std::move(obj));
    }

    const Garbage_collector::Object_ptr_container& Garbage_collector::get_registered_objects() const noexcept
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
            Object* obj = obj_pair.second.m_object.get();

            if (!obj)
                m_registered_objects.erase(obj);
            else
                obj->destruct();
        }

        finalize_destruction_on_objects();
    }

    void Garbage_collector::garbage_collect()
    {
        check_object(m_registered_objects.at(m_root));
        destruct_unchecked_objects();
    }

    void Garbage_collector::check_object(Tracked_obj& obj)
    {
        if (obj.m_is_checked || !is_object_valid(obj.m_object.get()))
            return;

        obj.m_is_checked = true;
        std::vector<Object*> owned_objects;
        obj.m_object->get_owned_objects(owned_objects);

        for (const Object* obj : owned_objects)
        {
            auto found_obj = m_registered_objects.find(obj);

            if (found_obj != m_registered_objects.end())
                check_object(found_obj->second);
        }
    }

    void Garbage_collector::destruct_unchecked_objects()
    {
        if (m_registered_objects.size() == 0)
            return;

        for (auto& obj_pair : m_registered_objects)
        {
            Object* obj = obj_pair.second.m_object.get();

            if (obj == nullptr)
                throw std::logic_error("obj should never be nullptr");

            if (!obj_pair.second.m_is_checked)
                obj->destruct();
            else
                obj_pair.second.m_is_checked = false;
        }
    }

    void Garbage_collector::finalize_destruction_on_objects()
    {
        auto it = m_registered_objects.begin();
        while (it != m_registered_objects.end())
        {
            if (is_object_valid(it->first) && it->first->is_marked_for_destruction())
                it = m_registered_objects.erase(it);
            else
                ++it;
        }
    }
} // namespace MEngine
