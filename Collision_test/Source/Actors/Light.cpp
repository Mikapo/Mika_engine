#include "Light.h"

#include "Objects/Components/Scene_components/Light_component.h"
#include "Objects/Components/Scene_components/Mesh_component.h"


void Light::initialize()
{
	Actor::initialize();

	create_component(Light_component::static_class());
}
