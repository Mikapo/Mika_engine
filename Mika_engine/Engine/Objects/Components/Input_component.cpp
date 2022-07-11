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
        if (!mapping)
            return;

        mapping->broadcast(mapping->get_current_value());
    }
}

void Input_component::remove_axis_mapping(const std::string& name) noexcept { m_axis_mappings.erase(name); }

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
        if (!mapping)
            return;

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
    if (!m_action_mappings.contains(key))
        return;

    auto& action_mappings = m_action_mappings.at(key);

    for (auto& value : action_mappings)
    {
        auto* action_mapping = value.get();

        if (action_mapping && action_mapping->get_action() == action)
            action_mapping->broadcast();
    }
}
