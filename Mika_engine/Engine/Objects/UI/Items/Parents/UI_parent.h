#pragma once

#include "../UI_item.h"
#include <set>

namespace Mika_engine
{
    struct UI_wrapper
    {
        UI_item* m_item;
        int32_t m_position;

        std::partial_ordering operator<=>(const UI_wrapper& other) const noexcept
        {
            return m_position <=> other.m_position;
        }
    };

    class UI_parent : public UI_item
    {
        GENERATED_BODY(UI_parent)

    public:
        UI_item* create_children(Class_obj* class_obj, std::string_view name, int32_t position);
        void update(float deltatime) override;
        void get_owned_objects(std::vector<Object*>& out_array) noexcept override;

        template <typename T>
        T* create_children_cast(Class_obj* class_obj, std::string_view name, int32_t position)
        {
            return dynamic_cast<T*>(create_children(class_obj, name, position));
        }

    protected:
        void draw_children();

    private:
        std::set<UI_wrapper> m_children;
    };

} // namespace Mika_engine
