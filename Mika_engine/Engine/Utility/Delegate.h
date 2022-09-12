#pragma once

#include <functional>
#include <memory>
#include <stdexcept>
#include <unordered_map>

class Object;
class Mika_engine;
template <typename... Argtypes>
class Obj_callback_interface
{
public:
    virtual ~Obj_callback_interface() = default;
    virtual bool invoke(Argtypes... args) = 0;
};

template <typename T, typename Callback, typename... Argtypes>
class Obj_callback : public Obj_callback_interface<Argtypes...>
{
public:
    Obj_callback(T* obj, Callback callback) noexcept : m_obj(obj), m_callback(std::forward<Callback>(callback))
    {
        m_engine = obj->get_engine();
    }

    bool invoke(Argtypes... args) override
    {
        if (T::static_is_valid(m_engine, m_obj))
        {
            std::invoke(m_callback, m_obj, std::forward<Argtypes>(args)...);
            return true;
        }

        return false;
    }

private:
    T* m_obj;
    Callback m_callback;
    Mika_engine* m_engine;
};

template <typename... Argtypes>
class Delegate
{
public:
    typedef std::unique_ptr<Obj_callback_interface<Argtypes...>> Callback_interface_ptr;

    template <typename T, typename Callback>
    void add_object(T* obj, Callback callback)
    {
        if (!obj)
            throw std::invalid_argument("obj was null");

        auto delegate_function = std::make_unique<Obj_callback<T, Callback, Argtypes...>>(obj, callback);

        m_callbacks.emplace(obj, std::move(delegate_function));
    }

    void remove_object(Object* obj)
    {
        if (!obj)
            throw std::invalid_argument("obj was null");

        m_callbacks.erase(obj);
    }

    void broadcast(Argtypes... args)
    {
        auto it = m_callbacks.begin();
        while (it != m_callbacks.end())
        {
            const bool success = it->second->invoke(std::forward<Argtypes>(args)...);

            if (success)
                ++it;
            else
                it = m_callbacks.erase(it);
        }
    }

private:
    std::unordered_map<Object*, Callback_interface_ptr> m_callbacks;
};
