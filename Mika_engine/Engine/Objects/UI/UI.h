#pragma once

#include "Items/Parents/UI_window.h"
#include "Objects/Object.h"
#include <unordered_set>

class World;
class UI_window;
class UI : public Object
{
    GENERATED_BODY(UI)

public:
    UI_window* create_window(std::string_view name, Class_obj* class_obj = UI_window::static_class());
    void draw();
    void update(float deltatime) override;
    void get_owned_objects(std::vector<Object*>& out_array) noexcept override;
    void add_to_viewport(World* world);
    void remove_from_viewport(World* world);

    Delegate<World*> m_on_added_to_viewport;

private:
    std::unordered_set<UI_window*> m_windows;
};
