#include "UI_item.h"

void UI_item::set_name(const std::string& name)
{
	m_name = name;
}

std::string_view UI_item::get_name() const
{
	return m_name;
}
