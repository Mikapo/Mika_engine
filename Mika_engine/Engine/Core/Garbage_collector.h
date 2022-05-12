#pragma once

#include <unordered_set>
#include <vector>

class Object;
class Garbage_collector
{
public:
	bool is_object_valid(Object* obj) const;
	void register_object(Object* obj);
	const std::unordered_set<Object*>& get_registered_objects() const;
	void unregister_object(Object* obj);
	void set_root_object(Object* obj);
	void mark_object_for_destruction(Object* obj);
	void update();
	void cleanup();

private:
	void garbage_collect();
	void check_object(Object* obj);
	void destruct_unchecked_objects();
	void finalize_destruction_on_objects();

	std::unordered_set<Object*> m_registered_objects;
	std::vector<Object*> m_objects_to_destroy;
	Object* m_root = nullptr;
};

