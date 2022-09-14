#include "Collapsing_header.h"

namespace Mika_engine
{
    void Collapsing_header::draw()
    {
        if (ImGui::CollapsingHeader(get_name().data()))
            draw_children();
    }
} // namespace Mika_engine
