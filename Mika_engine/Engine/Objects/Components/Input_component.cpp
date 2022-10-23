#include "Core/Engine.h"

#include "Input_component.h"

namespace MEngine
{
    void Input_component::initialize()
    {
        Actor_component::initialize();

        get_engine()->m_on_input.add_object(this, &Input_component::on_input);
    }

    void Input_component::update(float deltatime)
    {
        Actor_component::update(deltatime);

        for (auto& value : m_axis_mappings)
        {
            auto* mapping = value.second.get();
            if (!mapping)
                return;

            mapping->m_delegate.broadcast(mapping->m_current_value);
        }
    }

    void Input_component::remove_axis_mapping(const std::string& name) noexcept
    {
        m_axis_mappings.erase(name);
    }

    void Input_component::on_input(Input input)
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

            if (input.action == Input_action::release && input.key == mapping->m_current_key)
                mapping->m_current_value = 0.0F;

            else if (input.action == Input_action::press && mapping->m_keys.contains(input.key))
            {
                mapping->m_current_value = mapping->m_keys.at(input.key);
                mapping->m_current_key = input.key;
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

            if (action_mapping && action_mapping->m_action == input.action)
                action_mapping->m_delegate.broadcast();
        }
    }

} // namespace MEngine
