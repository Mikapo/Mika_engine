#pragma once


#include "Core/Mika_engine.h"
#include "Debug/Debug_logger.h"
#include <utility>
#include <vector>

class Mika_engine;
class Object
{
public:
	virtual ~Object() = default;

	template<typename T, typename... argtypes>
	static T* construct_object(Mika_engine* engine, argtypes... args)
	{
		T* obj = new T(std::forward<argtypes>(args)...);
		Object* default_object = obj;
		default_object->set_engine(engine);
		engine->register_object(obj);
		Debug_logger::get().log_object_created(default_object->get_class_name(), engine->get_amount_of_registered_objects());
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
	const Mika_engine* get_engine() const;
	virtual void update(float deltatime) {}
	std::string get_class_name();

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

	bool is_valid(Object* obj);

private:
	void set_engine(Mika_engine* engine);

	Mika_engine* m_engine;
	bool m_garbage_collector_mark = false;
	bool m_marked_for_destruction = false;
};

