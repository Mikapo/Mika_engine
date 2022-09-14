#include "UI.h"

#include "Objects/World.h"

namespace Mika_engine
{
    void UI::update(float deltatime)
    {
        Object::update(deltatime);

        update_owned_objects(m_windows, deltatime);
    }

    UI_window* UI::create_window(std::string_view name, Class_obj* class_obj)
    {
        if (!class_obj)
            throw std::invalid_argument("class_obj is null");

        UI_window* window_obj = class_obj->construct_cast<UI_window>(get_engine());
        if (!window_obj)
            return nullptr;

        m_windows.insert(window_obj);
        window_obj->set_name(name.data());
        window_obj->initialize();
        return window_obj;
    }

    void UI::draw()
    {
        for (UI_window* window : m_windows)
            if (window && is_valid(window))
                window->draw();
    }

    void UI::get_owned_objects(std::vector<Object*>& out_array) noexcept
    {
        for (UI_window* window : m_windows)
            out_array.push_back(window);
    }

    void UI::add_to_viewport(World* world)
    {
        if (!world)
            throw std::invalid_argument("world is null");

        if (is_valid(world))
            world->add_UI_to_viewport(this);
    }

    void UI::remove_from_viewport(World* world)
    {
        if (!world)
            throw std::invalid_argument("world is null");

        if (is_valid(world))
            world->add_UI_to_viewport(this);
    }

} // namespace Mika_engine
