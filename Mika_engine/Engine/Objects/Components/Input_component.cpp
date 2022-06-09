#include "Input_component.h"
#include "Core/Mika_engine.h"

void Input_component::initialize()
{
	Actor_component::initialize();

	get_engine()->m_on_key_event.add_object(this, &Input_component::on_key_event);
}

void Input_component::update(float deltatime)
{
	Actor_component::update(deltatime);

	for (auto& value : m_axis_mappings)
	{
		auto* mapping = value.second.get();
		mapping->broadcast(mapping->get_current_value());
	}
}

void Input_component::remove_axis_mapping(const std::string& name)
{
	m_axis_mappings.erase(name);
}

void Input_component::on_key_event(Input input)
{
    handle_axis_mapping(input.action, input.key);
    handle_action_mapping(input.action, input.key);
}

void Input_component::handle_axis_mapping(int32_t action, int32_t key)
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

void Input_component::handle_action_mapping(int32_t action, int32_t key) 
{
    auto& action_mappings = m_action_mappings[key];

	for (size_t i = 0; i < action_mappings.size(); ++i)
        if (action_mappings[i]->get_action() == action)
            action_mappings[i]->broadcast();
}

