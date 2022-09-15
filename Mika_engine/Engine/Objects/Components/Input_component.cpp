#include "Core/Engine.h"

#include "Input_component.h"

namespace Mika_engine
{
    void Input_component::initialize()
    {
        Actor_component::initialize();

        get_engine()->m_on_input.add_object(this, &Input_component::on_key_event);
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

    void Input_component::remove_axis_mapping(const std::string& name) noexcept
    {
        m_axis_mappings.erase(name);
    }

    void Input_component::on_key_event(Input input)
    {
        handle_axis_mapping(input);
        handle_action_mapping(input);
    }

    void Input_component::handle_axis_mapping(Input input)
    {
        for (auto& value : m_axis_mappings)
        {
            auto* mapping = value.second.get();
            if (!mapping)
                return;

            if (input.action == Input_action::release && input.key == mapping->get_current_key())
                mapping->set_current_value(0.0f);

            else if (input.action == Input_action::press && mapping->get_keys().contains(input.key))
            {
                mapping->set_current_value(mapping->get_keys().at(input.key));
                mapping->set_current_key(input.key);
            }
        }
    }

    void Input_component::handle_action_mapping(Input input)
    {
        if (!m_action_mappings.contains(input.key))
            return;

        auto& action_mappings = m_action_mappings.at(input.key);

        for (auto& value : action_mappings)
        {
            auto* action_mapping = value.get();

            if (action_mapping && action_mapping->get_action() == input.action)
                action_mapping->broadcast();
        }
    }

} // namespace Mika_engine
