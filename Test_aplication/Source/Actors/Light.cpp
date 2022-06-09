#include "Light.h"

#include "Objects/Components/Scene_components/Light_component.h"
#include "Objects/Components/Scene_components/Mesh_component.h"


void Light::initialize()
{
	Actor::initialize();

	m_light_component = create_component_cast<Light_component>(Light_component::static_class());
	set_location( { 0.0f, 5.0f, 7.0f } );
}

void Light::change_light_color(glm::vec4 color)
{
	m_light_component->set_color(color);
}
