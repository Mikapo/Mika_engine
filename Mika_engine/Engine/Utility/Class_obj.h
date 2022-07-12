#pragma once

#include "Debug/Debug_logger.h"
#include <memory>
#include <string_view>
#include <unordered_map>

class Mika_engine;
class Object;
class Class_obj
{
public:
    virtual ~Class_obj() = default;

    template <typename T>
    T* construct_cast(Mika_engine* engine)
    {
        return dynamic_cast<T*>(construct(engine));
    }

    virtual Object* construct(Mika_engine* engine) = 0;
    virtual std::string_view get_name() = 0;
};

template <typename T>
class Class_obj_template : public Class_obj
{
public:
    Class_obj_template(std::string_view name) noexcept : m_name(name)
    {
    }

    Object* construct(Mika_engine* engine) override
    {
        std::unique_ptr<T> unique_ptr_obj = std::make_unique<T>();
        unique_ptr_obj->set_engine(engine);

        LOG(notification, objects, "Object created with name {}", get_name());

        T* obj = unique_ptr_obj.get();
        T::template register_object(engine, std::move(unique_ptr_obj));
        return obj;
    }

    std::string_view get_name() noexcept override
    {
        return m_name;
    }

private:
    std::string_view m_name;
};

class Class
{
public:
    template <typename T>
    static Class_obj* get()
    {
        std::string_view class_name = T::static_get_name();

        if (!m_classes.contains(class_name))
            m_classes[class_name] = std::make_unique<Class_obj_template<T>>(class_name);

        return m_classes[class_name].get();
    }

    static void cleanup() noexcept
    {
        m_classes.clear();
    }

private:
    static std::unordered_map<std::string_view, std::unique_ptr<Class_obj>> m_classes;
};
