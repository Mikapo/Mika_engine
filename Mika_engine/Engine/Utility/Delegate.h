#pragma once

#include <memory>
#include <unordered_map>

#include "Core/Mika_engine.h"

template<typename... argtypes>
class Delegate_function_interface
{
public:
	virtual ~Delegate_function_interface() = default;
	virtual bool call(argtypes... args) = 0;
};

template<typename T, typename... argtypes>
class Delegate_function : public Delegate_function_interface<argtypes...>
{
public:
	Delegate_function(T* obj, void(T::* f)(argtypes...))
		: m_obj(obj), m_f(f)
	{
		m_engine = obj->get_engine();
	}

	bool call(argtypes... args)
	{
		if (m_engine->is_object_valid(m_obj))
		{
			(m_obj->*m_f)(std::forward<argtypes>(args)...);
			return true;
		}

		return false;
	}

private:
	T* m_obj;
	void(T::* m_f)(argtypes...);
	Mika_engine* m_engine;

};

template<typename... argtypes>
class Delegate
{
public:
	typedef std::unique_ptr<Delegate_function_interface<argtypes...>> delegate_function_ptr;

	template<typename T>
	void add_object(T* obj, void(T::* f)(argtypes...))
	{
		delegate_function_ptr delegate_function = std::make_unique<Delegate_function<T, argtypes...>>(obj, f);
		m_functions.emplace(obj, std::move(delegate_function));
	}

	void remove_object(Object* obj)
	{
		m_functions.erase(obj);
	}

	bool call(argtypes... args)
	{
		std::vector<Object*> destroy;

		for (auto& function : m_functions)
			if (!function.second->call(std::forward<argtypes>(args)...))
				destroy.push_back(function.first);

		for (Object* obj : destroy)
			m_functions.erase(obj);

		return m_functions.size() > 0;
	}
	
private:
	std::unordered_map<Object*, delegate_function_ptr> m_functions;
};
