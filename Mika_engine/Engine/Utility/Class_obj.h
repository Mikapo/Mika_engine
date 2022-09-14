#pragma once

#include "Debug/Debug_logger.h"
#include <memory>
#include <string_view>
#include <unordered_map>

namespace Mika_engine
{
    class Engine;
    class Object;
    class Class_obj
    {
    public:
        virtual ~Class_obj() = default;

        template <typename T>
        T* construct_cast(Engine* engine)
        {
            return dynamic_cast<T*>(construct(engine));
        }

        virtual Object* construct(Engine* engine) = 0;
        virtual std::string_view get_name() = 0;
    };

    template <typename T>
    class Class_obj_template : public Class_obj
    {
    public:
        Class_obj_template(std::string_view name) noexcept : m_name(name)
        {
        }

        Object* construct(Engine* engine) override
        {
            return T::template construct_object<T>(engine);
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

            auto found_class = m_classes.find(class_name);

            if (found_class == m_classes.end())
            {
                std::unique_ptr new_class = std::make_unique<Class_obj_template<T>>(class_name);
                m_classes.emplace(class_name, std::move(new_class));
                return m_classes.at(class_name).get();
            }

            return found_class->second.get();
        }

        static void cleanup() noexcept
        {
            m_classes.clear();
        }

    private:
        static std::unordered_map<std::string_view, std::unique_ptr<Class_obj>> m_classes;
    };

}
