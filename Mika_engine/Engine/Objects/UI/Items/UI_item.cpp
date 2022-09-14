#include "UI_item.h"

namespace Mika_engine
{
    void UI_item::set_name(const std::string& name)
    {
        m_name = name;
    }

    std::string_view UI_item::get_name() const noexcept
    {
        return m_name;
    }
}

