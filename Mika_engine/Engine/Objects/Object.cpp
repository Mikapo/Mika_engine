#include "Object.h"
#include "Core/Mika_engine.h"
#include <string>

void Object::destruct()
{
	m_marked_for_destruction = true;
    get_engine()->mark_object_for_destruction(this);
}

void Object::set_garbage_collect_mark(bool mark)
{
	m_garbage_collector_mark = mark;
}

bool Object::is_marked_by_garbage_collector() const
{
	return m_garbage_collector_mark;
}

bool Object::is_marked_for_destruction() const
{
	return m_marked_for_destruction;
}

Mika_engine* Object::get_engine()
{
	return m_engine; 
}

Asset_manager& Object::get_asset_manager() 
{ 
	return get_engine()->get_asset_manager(); 
}

const Mika_engine* Object::get_engine() const
{
	return m_engine; }

void Object::update(float deltatime) 
{
	if (m_lifetime_has_been_set)
	{
		using namespace std::chrono;
        auto time_since_lifetime_has_been_set = high_resolution_clock::now() - m_time_since_lifetime_has_been_set;

        if (time_since_lifetime_has_been_set.count() * 0.000000001f > m_lifetime)
            destruct();
	}
}

std::string Object::get_class_name()
{
	return std::string(typeid(*this).name()).substr(6);
}

void Object::finalize_destruction()
{
    m_on_being_destroyed.broadcast(this);
    unregister_object();
	Debug_logger::get().log_object_destroyed(get_class_name(), m_engine->get_amount_of_registered_objects());
	delete this;
}

void Object::register_object() 
{ 
	get_engine()->register_object(this); 
}

void Object::unregister_object() 
{ 
	get_engine()->unregister_object(this); 
}

bool Object::is_valid(Object* obj) 
{ 
	return static_is_valid(get_engine(), obj); 
}

bool Object::static_is_valid(Mika_engine* engine, Object* obj) 
{ 
	return engine->is_object_valid(obj); 
}

void Object::set_lifetime(float lifetime) 
{ 
	m_lifetime_has_been_set = true;
    m_time_since_lifetime_has_been_set = std::chrono::high_resolution_clock::now();
    m_lifetime = lifetime;
}

void Object::set_engine(Mika_engine* engine)
{
	m_engine = engine;
}

size_t Object::get_amount_of_registered_objects() 
{ 
	return get_engine()->get_amount_of_registered_objects(); 
}