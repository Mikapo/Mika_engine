#include "Input_component.h"

#include <iostream>

void Input_component::initialize()
{
	Actor_component::initialize();

	get_engine()->subscribe_for_key_events(this);
}

void Input_component::update(float deltatime)
{
	Actor_component::update(deltatime);

	std::vector<std::string> remove;

	for (auto& value : m_axis_mappings)
	{
		auto* mapping = value.second.get();
		const bool success = mapping->call(mapping->get_current_value());

		if (!success)
			remove.push_back(value.first);
	}

	for (auto& mapping_string : remove)
		m_axis_mappings.erase(mapping_string);

	remove.clear();
}

void Input_component::remove_axis_mapping(const std::string& name)
{
	m_axis_mappings.erase(name);
}

void Input_component::on_key_event(int32_t key, int32_t scancode, int32_t action, int32_t mods)
{
	for (auto& value : m_axis_mappings)
	{
		auto* mapping = value.second.get();

		if (action == GLFW_RELEASE && key == mapping->get_current_key())
			mapping->set_current_value(0.0f);

		else if (action == GLFW_PRESS && mapping->get_keys().contains(key))
		{
			mapping->set_current_value(mapping->get_keys().at(key));
			mapping->set_current_key(key);
		}
	}
}

