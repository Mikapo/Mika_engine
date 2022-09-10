#pragma once

#include "Debug/Debug_logger.h"
#include "Utility/Class_obj.h"
#include "Utility/Delegate.h"
#include "Utility/Macros/Generated_body.h"
#include "gsl/gsl"
#include <chrono>
#include <typeinfo>
#include <unordered_set>
#include <utility>
#include <vector>

class Asset_manager;
class Mika_engine;
class Object
{
    FIRST_GENERATED_BODY(Object)

public:
    Object() = default;
    Object(const Object&) = delete;
    Object(Object&&) = delete;
    virtual ~Object() = default;

    Object& operator=(const Object&) = delete;
    Object&& operator=(Object&&) = delete;

    template <typename T>
    static T* construct_object(Mika_engine* engine)
    {
        std::unique_ptr<T> unique_ptr_obj = std::make_unique<T>();
        unique_ptr_obj->set_engine(engine);

        LOG(notification, objects, "Created object with name {}", unique_ptr_obj->get_class_name());

        T* obj = unique_ptr_obj.get();
        register_object(engine, std::move(unique_ptr_obj));
        return obj;
    }

    virtual void destruct() noexcept;
    virtual void get_owned_objects(std::vector<Object*>& out_array) noexcept
    {
    }
    void set_garbage_collect_mark(bool mark) noexcept;
    bool is_marked_by_garbage_collector() const noexcept;
    bool is_marked_for_destruction() const noexcept;
    virtual void initialize()
    {
    }
    Mika_engine* get_engine() noexcept;
    void set_engine(Mika_engine* engine) noexcept;
    Asset_manager& get_asset_manager() noexcept;
    const Mika_engine* get_engine() const noexcept;
    virtual void update(float deltatime);
    std::string_view get_class_name();
    size_t get_amount_of_registered_objects() noexcept;
    static bool static_is_valid(const Mika_engine* engine, const Object* obj);
    void set_lifetime(float lifetime) noexcept;
    static void register_object(Mika_engine* engine, std::unique_ptr<Object> obj);

protected:
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

    template <typename object_type>
    void remove_object_from_set(std::unordered_set<object_type*>& set, Object* obj)
    {
        if (object_type* casted_obj = dynamic_cast<object_type*>(obj))
            set.erase(casted_obj);
        else
            throw std::runtime_error("object is wrong type");
    }

    bool is_valid(const Object* obj) const;

private:
    Mika_engine* m_engine = nullptr;
    bool m_garbage_collector_mark = false;
    bool m_marked_for_destruction = false;

    bool m_lifetime_has_been_set = false;
    std::chrono::steady_clock::time_point m_time_since_lifetime_has_been_set;
    float m_lifetime = 0.0f;
};
