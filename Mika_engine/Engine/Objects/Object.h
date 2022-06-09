#pragma once

#include "Debug/Debug_logger.h"
#include <utility>
#include <vector>
#include <unordered_set>
#include "Utility/Delegate.h"
#include <chrono>
#include "utility/GENERATED_BODY.h"
#include "Utility/Class_obj.h"
#include <typeinfo>

class Asset_manager;
class Mika_engine;
class Object
{
    GENERATED_BODY(Object)

public:
	virtual ~Object() = default;
	template<typename T, typename... argtypes>
	static T* construct_object(Mika_engine* engine, argtypes... args)
	{
		T* obj = new T(std::forward<argtypes>(args)...);
        obj->set_engine(engine);
        obj->register_object();
		Debug_logger::get().log_object_created(obj->get_class_name(), obj->get_amount_of_registered_objects());
		return obj;
	}

	void destruct();
	void finalize_destruction();
	virtual void get_owned_objects(std::vector<Object*>& out_array) {}
	void set_garbage_collect_mark(bool mark);
	bool is_marked_by_garbage_collector() const;
	bool is_marked_for_destruction() const;
	virtual void initialize() {}
	Mika_engine* get_engine();
    Asset_manager& get_asset_manager();
	const Mika_engine* get_engine() const;
    virtual void update(float deltatime);
	std::string get_class_name();
    size_t get_amount_of_registered_objects();
    static bool static_is_valid(Mika_engine* engine, Object* obj);
    void set_lifetime(float lifetime);

	Delegate<Object*> m_on_being_destroyed;

protected:
	template<typename object_type>
    void update_owned_objects(std::unordered_set<object_type*>& object_container, float deltatime)
    {
        std::vector<object_type*> destroy;

        for (object_type* item : object_container)
            if (is_valid(item))
                item->update(deltatime);
            else
                destroy.push_back(item);

        for (object_type* item : destroy)
            object_container.erase(item);
    }

	template<typename object_type>
	void remove_object_from_set(std::unordered_set<object_type*>& set, Object* obj)
	{
        if (object_type* casted_obj = dynamic_cast<object_type*>(obj))
        {
			set.erase(casted_obj);
        }
        else
            throw std::runtime_error("object is wrong type");
	}

	bool is_valid(Object* obj);

private:
	void set_engine(Mika_engine* engine);
    void register_object();
    void unregister_object();

	Mika_engine* m_engine = nullptr;
	bool m_garbage_collector_mark = false;
	bool m_marked_for_destruction = false;

	bool m_lifetime_has_been_set = false;
    std::chrono::steady_clock::time_point m_time_since_lifetime_has_been_set;
    float m_lifetime = 0.0f;
};

