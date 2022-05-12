#include "Collapsing_header.h"

void Collapsing_header::draw()
{
	if (ImGui::CollapsingHeader(get_name().data()))
		draw_children();
}
