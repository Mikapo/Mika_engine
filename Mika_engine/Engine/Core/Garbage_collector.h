#pragma once

#include <unordered_map>
#include <vector>
#include <memory>

class Object;
class Garbage_collector
{
public:
	bool is_object_valid(const Object* obj) const;
	void register_object(std::unique_ptr<Object> obj);
    const std::unordered_map<Object*, std::unique_ptr<Object>>& get_registered_objects() const noexcept;
	void set_root_object(Object* obj);
	void update();
	void cleanup();

private:
	void garbage_collect();
	void check_object(Object* obj);
	void destruct_unchecked_objects();
	void finalize_destruction_on_objects();

	std::unordered_map<Object*, std::unique_ptr<Object>> m_registered_objects;
	std::vector<Object*> m_objects_to_destroy;
	Object* m_root = nullptr;
};

