#pragma once

#include "ImGui/imgui.h"
#include "Objects/Object.h"
#include <string>

namespace MEngine
{
    class UI_item : public Object
    {
        GENERATED_BODY(UI_item)

    public:
        virtual void draw()
        {
        }
        void set_name(const std::string& name);
        std::string_view get_name() const noexcept;

    private:
        std::string m_name = "default name";
    };
} // namespace MEngine
