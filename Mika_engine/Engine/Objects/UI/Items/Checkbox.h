#pragma once

#include "UI_item.h"
#include "Utility/Delegate.h"

namespace MEngine
{
    class Checkbox : public UI_item
    {
        GENERATED_BODY(Checkbox)

    public:
        void draw() override;
        void update(float deltatime) override;
        void set_checked(bool checked) noexcept;

        Delegate<bool> m_on_checked_change;

    private:
        bool m_is_checked = false;
        bool m_was_checked_in_last_check = false;
    };
} // namespace MEngine
