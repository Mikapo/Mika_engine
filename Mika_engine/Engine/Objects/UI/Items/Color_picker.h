#pragma once

#include "UI_item.h"
#include "Utility/Delegate.h"
#include "glm/vec4.hpp"
#include <array>

namespace Mika_engine
{
    class Color_picker : public UI_item
    {
        GENERATED_BODY(Color_picker)

    public:
        void draw() override;
        void update(float deltatime) override;
        void add_flag(ImGuiColorEditFlags flag) noexcept;

        Delegate<glm::vec4> m_on_color_change;

    private:
        ImGuiColorEditFlags m_flags = ImGuiColorEditFlags_::ImGuiColorEditFlags_None;

        std::array<float, 4> m_current_color = {0.0f, 0.0f, 0.0f, 0.0f};
        std::array<float, 4> m_previously_checked_color = {0.0f, 0.0f, 0.0f, 0.0f};
    };
} // namespace Mika_engine
