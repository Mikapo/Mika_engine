#include "Light.h"

#include "Objects/Components/Scene_components/Light_component.h"
#include "Objects/Components/Scene_components/Mesh_component.h"

void Light::initialize()
{
    Actor::initialize();

    create_component(Mika_engine::Light_component::static_class());
}
