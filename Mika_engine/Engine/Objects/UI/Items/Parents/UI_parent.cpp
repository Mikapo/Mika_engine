#include "UI_parent.h"

UI_item* UI_parent::create_children(Class_obj* class_obj, std::string_view name, int32_t position)
{
    if (!class_obj)
        throw std::invalid_argument("class_obj is null");

    UI_item* children = class_obj->construct_cast<UI_item>(get_engine());
    if (!children)
        return nullptr;

    m_children.insert({children, position});
    m_positions.insert({children, position});
    children->set_name(name.data());
    children->m_on_being_destroyed.add_object(this, &UI_parent::on_chidren_destroyed);
    children->initialize();
    return children;
}

void UI_parent::update(float deltatime)
{
    UI_item::update(deltatime);

    std::vector<UI_wrapper> destroy;

    for (const UI_wrapper wrapper : m_children)
        if (is_valid(wrapper.m_item))
            wrapper.m_item->update(deltatime);
        else
            destroy.push_back(wrapper);

    for (const UI_wrapper wrapper : destroy)
        m_children.erase(wrapper);
}

void UI_parent::get_owned_objects(std::vector<Object*>& out_array) noexcept
{
    for (UI_wrapper wrapper : m_children)
        out_array.push_back(wrapper.m_item);
}

void UI_parent::draw_children()
{
    for (UI_wrapper wrapper : m_children)
        if (is_valid(wrapper.m_item))
            wrapper.m_item->draw();
}

void UI_parent::on_chidren_destroyed(Object* children)
{
    if (auto* casted_children = dynamic_cast<UI_item*>(children))
    {
        const int32_t position = m_positions.at(casted_children);
        m_positions.erase(casted_children);
        m_children.erase({casted_children, position});
    }
    else
        throw std::runtime_error("wrong type");
}
