#include "UI_parent.h"

void UI_parent::update(float deltatime)
{
	UI_item::update(deltatime);

	std::vector<UI_wrapper> destroy;

	for (UI_wrapper wrapper : m_children)
		if (is_valid(wrapper.m_item))
			wrapper.m_item->update(deltatime);
		else
			destroy.push_back(wrapper);

	for (UI_wrapper wrapper : destroy)
		m_children.erase(wrapper);
}

void UI_parent::get_owned_objects(std::vector<Object*>& out_array)
{
	for (UI_wrapper wrapper : m_children)
		if (is_valid(wrapper.m_item))
			out_array.push_back(wrapper.m_item);
}

void UI_parent::draw_children()
{
	for (UI_wrapper wrapper : m_children)
		if (is_valid(wrapper.m_item))
			wrapper.m_item->draw();
}
