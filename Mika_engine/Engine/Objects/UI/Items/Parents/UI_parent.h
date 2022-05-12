#pragma once

#include "../UI_item.h"
#include <set>

struct UI_wrapper
{
	UI_item* m_item;
	int32_t m_position;

	std::partial_ordering operator<=>(const UI_wrapper& other) const
	{
		return m_position <=> other.m_position;
	}
};

class UI_parent : public UI_item
{
public:
	template<typename T>
	T* create_children(std::string_view name, int32_t position)
	{
		T* object = Object::construct_object<T>(get_engine());
		UI_item* basic_item = object;
		m_children.insert({ basic_item, position});
		basic_item->set_name(name.data());
		basic_item->initialize();
		return object;
	}

	void update(float deltatime) override;
	void get_owned_objects(std::vector<Object*>& out_array) override;

protected:
	void draw_children();

private:
	std::set<UI_wrapper> m_children;
};

