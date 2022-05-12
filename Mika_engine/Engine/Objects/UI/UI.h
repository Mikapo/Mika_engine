#pragma once

#include "Objects/Object.h"
#include <unordered_set>
#include "Items/Parents/UI_window.h"

class UI_window;
class UI : public Object
{
public:
	template<typename T = UI_window>
	T* add_window(std::string_view name)
	{
		T* window_obj = Object::construct_object<T>(get_engine());
		UI_window* window = window_obj;
		m_windows.insert(window);
		window->set_name(name.data());
		window->initialize();
		return window_obj;
	}
	
	void draw();
	void update(float deltatime) override;
	void get_owned_objects(std::vector<Object*>& out_array) override;
	void add_to_viewport(World* world);
	void remove_from_viewport(World* world);
	virtual void on_added_to_viewport(World* world) {};

private:
	std::unordered_set<UI_window*> m_windows;
};

