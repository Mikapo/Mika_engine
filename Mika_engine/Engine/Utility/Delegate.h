#pragma once

#include <memory>
#include <unordered_map>
#include <functional>
#include <stdexcept>

class Object;
class Mika_engine;
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
    Delegate_function(T* obj, void (T::*f)(argtypes...)) noexcept
		: m_obj(obj), m_f(f)
	{
		m_engine = obj->get_engine();
	}

	bool call(argtypes... args) override
	{
		if (T::static_is_valid(m_engine, m_obj))
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
        if (!obj)
            throw std::invalid_argument("obj was null");

		delegate_function_ptr delegate_function = std::make_unique<Delegate_function<T, argtypes...>>(obj, f);
		m_obj_functions.emplace(obj, std::move(delegate_function));
	}

	void add_function(void* obj, const std::function<void(argtypes...)> f)
	{ 
		if (!obj)
            throw std::invalid_argument("obj was null");

		m_functions.emplace(obj, f);
	}

	void remove_object(Object* obj) 
	{ 
		if (!obj)
            throw std::invalid_argument("obj was null");

		m_obj_functions.erase(obj);
	}

	void remove_function(void* obj)
	{ 
		if (!obj)
            throw std::invalid_argument("obj was null");

		m_functions.erase(obj);
	}

	void broadcast(argtypes... args)
	{
        std::vector<Object*> destroy;

		for (auto& function : m_obj_functions)
			if (!function.second->call(std::forward<argtypes>(args)...))
				destroy.push_back(function.first);

		for (Object* obj : destroy)
            m_obj_functions.erase(obj);

		for (auto& function : m_functions)
            function.second(std::forward<argtypes>(args)...);
	}
	
private:
    std::unordered_map<Object*, delegate_function_ptr> m_obj_functions;
    std::unordered_map<void*, std::function<void(argtypes...)>> m_functions;
};
