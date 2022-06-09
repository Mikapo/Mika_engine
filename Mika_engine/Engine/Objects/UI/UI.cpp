#include "UI.h"

#include "Objects/World.h"


void UI::update(float deltatime)
{
	Object::update(deltatime);

	update_owned_objects(m_windows, deltatime);
}

UI_window* UI::create_window(std::string_view name, Class_obj* class_obj) 
{ 
	UI_window* window_obj = class_obj->construct_cast<UI_window>(get_engine());
    m_windows.insert(window_obj);
    window_obj->set_name(name.data());
    window_obj->m_on_being_destroyed.add_object(this, &UI::on_window_destructed);
    window_obj->initialize();
    return window_obj;
}


void UI::draw()
{
	for (UI_window* window : m_windows)
		if (is_valid(window))
			window->draw();
}

void UI::get_owned_objects(std::vector<Object*>& out_array)
{
	for (UI_window* window : m_windows)
		if (is_valid(window))
			out_array.push_back(window);
}

void UI::add_to_viewport(World* world)
{
	if (is_valid(world))
		world->add_UI_to_viewport(this);
}

void UI::remove_from_viewport(World* world)
{
	if (is_valid(world))
		world->add_UI_to_viewport(this);
}

void UI::on_window_destructed(Object* window) 
{ 
	remove_object_from_set(m_windows, window); 
}
