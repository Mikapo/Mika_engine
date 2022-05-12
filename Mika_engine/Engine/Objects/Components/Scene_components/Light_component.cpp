#include "Light_component.h"

#include "Objects/World.h"
#include "Utility/Frame_data.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

void Light_component::initialize()
{
	Scene_component::initialize();

	get_world()->register_light_component(this);
}

void Light_component::set_color(glm::vec4 color)
{
	m_color = color;
}

Light_data Light_component::get_light_data()
{
	Light_data data;
	data.m_color = m_color;
	data.m_light_transform = get_world_transform();
	return data;
}
