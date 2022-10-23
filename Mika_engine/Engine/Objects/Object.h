#pragma once

#include "Datatypes/Log_severity.h"
#include "Utility/Class_obj.h"
#include "Utility/Delegate.h"
#include "Utility/Macros/Generated_body.h"
#include "gsl/gsl"
#include <chrono>
#include <typeinfo>
#include <unordered_set>
#include <utility>
#include <vector>

namespace MEngine
{
    class Engine;

    // Represents object that can exist in the world
    class Object
    {
        FIRST_GENERATED_BODY(Object)

    public:
        Object() = default;
        virtual ~Object() = default;

        Object(const Object&) = delete;
        Object(Object&&) = delete;

        Object& operator=(const Object&) = delete;
        Object&& operator=(Object&&) = delete;

        // Constructs object and registers it with engine
        template <typename T>
        [[nodiscard]] static T* construct_object(Engine* engine)
        {
            if (engine == nullptr)
                throw std::invalid_argument("engine is null");

            std::unique_ptr<T> unique_ptr_obj = std::make_unique<T>();
            unique_ptr_obj->set_engine(engine);

            T* obj = unique_ptr_obj.get();
            register_object(engine, std::move(unique_ptr_obj));
            return obj;
        }

        // Prepares object to be destructed
        virtual void destruct() noexcept;

        // Gets objects that are owned by this object
        virtual void get_owned_objects(std::vector<Object*>& out_array) noexcept
        {
        }

        // Gets called when object is created
        virtual void initialize()
        {
        }

        // Gets called every frame
        virtual void update(float deltatime);

        // Registers object with the engine
        static void register_object(Engine* engine, std::unique_ptr<Object> obj);

        /**
         * The object will be destroyed after lifetime has passed
         *
         * @param Lifetime in seconds
         */
        void set_lifetime(float lifetime) noexcept;

        void set_engine(Engine* engine) noexcept;
        [[nodiscard]] const Engine* get_engine() const noexcept;
        [[nodiscard]] Engine* get_engine() noexcept;

        [[nodiscard]] bool is_marked_for_destruction() const noexcept;
        [[nodiscard]] std::string_view get_class_name();
        [[nodiscard]] size_t get_amount_of_registered_objects() noexcept;
        [[nodiscard]] static bool static_is_valid(const Engine* engine, const Object* obj);

    protected:
        // Calls update on every object in container and removes invalid objects from container
        template <typename object_type>
        void update_owned_objects(std::unordered_set<object_type*>& object_container, float deltatime)
        {
            auto it = object_container.begin();

            while (it != object_container.end())
            {
                if (is_valid(*it))
                {
                    (*it)->update(deltatime);
                    ++it;
                }
                else
                    it = object_container.erase(it);
            }
        }

        // Checks if the object is still valid to use
        [[nodiscard]] bool is_valid(const Object* obj) const;

    private:
        Engine* m_engine = nullptr;
        bool m_marked_for_destruction = false;

        bool m_lifetime_has_been_set = false;
        std::chrono::steady_clock::time_point m_time_since_lifetime_has_been_set;
        float m_lifetime = 0.0f;
    };
} // namespace MEngine
