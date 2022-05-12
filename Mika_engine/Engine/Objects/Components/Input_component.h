#pragma once

#include "Actor_component.h"
#include "Interfaces/Key_event_listener.h"
#include "Utility/Delegate.h"
#include <stdexcept>

class Axis_mapping
{
public:
	template<typename T>
	Axis_mapping(T* obj, void(T::* f)(float))
	{
		m_delegate.add_object(obj, f);
	}

	virtual bool call(float value)
	{
		return m_delegate.call(value);
	}

	void add_key(int32_t key, float value)
	{
		m_keys[key] = value;
	}

	float get_current_value() const { return m_current_value; }
	void set_current_value(float value) { m_current_value = value; }
	int32_t get_current_key() const { return m_current_key; }
	void set_current_key(int32_t new_key) { m_current_key = new_key; }
	const std::unordered_map<int32_t, float>& get_keys() const { return m_keys; }

private:

	float m_current_value = 0;
	int32_t m_current_key = 0;
	std::unordered_map<int32_t, float> m_keys;
	Delegate<float> m_delegate;
};

class Input_component : public Actor_component, public Key_event_listener
{
public:
	void on_key_event(int32_t key, int32_t scancode, int32_t action, int32_t mods) override;
	void initialize() override;
	void update(float deltatime) override;

	template<typename T>
	Axis_mapping* add_axis_mapping(const std::string& name, T* obj, void (T::* f)(float))
	{
		m_axis_mappings.emplace(name, new Axis_mapping(obj, f));
		return m_axis_mappings[name].get();
	}

	void remove_axis_mapping(const std::string& name);

private:
	std::unordered_map<std::string, std::unique_ptr<Axis_mapping>> m_axis_mappings;
};

