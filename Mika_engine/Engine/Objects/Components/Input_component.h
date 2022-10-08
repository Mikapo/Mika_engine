#pragma once

#include "Actor_component.h"
#include "Utility/Delegate.h"

#include "Datatypes/Input.h"
#include <stdexcept>

namespace MEngine
{
    class Axis_mapping
    {
    public:
        template <typename T>
        Axis_mapping(T* obj, void (T::*f)(float))
        {
            m_delegate.add_object(obj, f);
        }

        void broadcast(float value)
        {
            m_delegate.broadcast(value);
        }

        void add_key(Input_key key, float value)
        {
            m_keys[key] = value;
        }

        float get_current_value() const noexcept
        {
            return m_current_value;
        }
        void set_current_value(float value) noexcept
        {
            m_current_value = value;
        }
        Input_key get_current_key() const noexcept
        {
            return m_current_key;
        }
        void set_current_key(Input_key new_key) noexcept
        {
            m_current_key = new_key;
        }
        const std::unordered_map<Input_key, float>& get_keys() const noexcept
        {
            return m_keys;
        }

    private:
        float m_current_value = 0;
        Input_key m_current_key = Input_key::unkown;
        std::unordered_map<Input_key, float> m_keys;
        Delegate<float> m_delegate;
    };

    class Action_mapping
    {
    public:
        template <typename T>
        Action_mapping(const std::string& name, Input_key key, Input_action action, T* obj, void (T::*f)())
        {
            m_name = name;
            m_key = key;
            m_action = action;
            m_delegate.add_object(obj, f);
        }

        void broadcast()
        {
            m_delegate.broadcast();
        }

        Input_action get_action() noexcept
        {
            return m_action;
        }

    private:
        std::string m_name;
        Input_key m_key;
        Input_action m_action;
        Delegate<> m_delegate;
    };

    class Input_component : public Actor_component
    {
        GENERATED_BODY(Input_component)

    public:
        void initialize() override;
        void update(float deltatime) override;

        template <typename T>
        Axis_mapping* add_axis_mapping(const std::string& name, T* obj, void (T::*f)(float))
        {
            m_axis_mappings.emplace(name, new Axis_mapping(obj, f));
            return m_axis_mappings[name].get();
        }

        template <typename T>
        void add_action_mapping(const std::string& name, Input_key key, Input_action action, T* obj, void (T::*f)())
        {
            m_action_mappings[key].emplace_back(new Action_mapping(name, key, action, obj, f));
        }

        void remove_axis_mapping(const std::string& name) noexcept;

    private:
        void on_key_event(Input input);
        void handle_axis_mapping(Input input);
        void handle_action_mapping(Input input);

        std::unordered_map<std::string, std::unique_ptr<Axis_mapping>> m_axis_mappings;
        std::unordered_map<Input_key, std::vector<std::unique_ptr<Action_mapping>>> m_action_mappings;
    };

} // namespace MEngine
