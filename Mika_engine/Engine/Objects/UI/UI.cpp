#include "UI.h"

#include "Objects/World.h"


void UI::update(float deltatime)
{
	Object::update(deltatime);

	update_owned_objects(m_windows, deltatime);
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
