#include "Object.h"

void Object::destruct()
{
	m_marked_for_destruction = true;
	m_engine->mark_object_for_destruction(this);
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

const Mika_engine* Object::get_engine() const
{
	return m_engine;
}

std::string Object::get_class_name()
{
	return std::string(typeid(*this).name()).substr(6);
}

void Object::finalize_destruction()
{
	m_engine->unregister_object(this);
	Debug_logger::get().log_object_destroyed(get_class_name(), m_engine->get_amount_of_registered_objects());
	delete this;
}

bool Object::is_valid(Object* obj)
{
	return get_engine()->is_object_valid(obj);
}

void Object::set_engine(Mika_engine* engine)
{
	m_engine = engine;
}
