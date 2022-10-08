#pragma once

#include "Objects/Actor.h"

namespace Mika_engine
{
    class Mesh_component;
}

class Cube : public Mika_engine::Actor
{
    GENERATED_BODY(Cube)

public:
    void initialize() override;
    void set_color(glm::vec4 color);

private:
    Mika_engine::Mesh_component* m_mesh_component = nullptr;
};
