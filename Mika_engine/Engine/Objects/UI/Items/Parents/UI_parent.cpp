#include "UI_parent.h"

UI_item* UI_parent::create_children(Class_obj* class_obj, std::string_view name, int32_t position)
{
    if (!class_obj)
        throw std::invalid_argument("class_obj is null");

    UI_item* children = class_obj->construct_cast<UI_item>(get_engine());
    if (!children)
        return nullptr;

    m_children.insert({children, position});
    children->set_name(name.data());
    children->initialize();
    return children;
}

void UI_parent::update(float deltatime)
{
    UI_item::update(deltatime);

    //todo make removing children more optimal
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
    // todo make thread safe
    for (UI_wrapper wrapper : m_children)
        if (is_valid(wrapper.m_item))
            wrapper.m_item->draw();
}
