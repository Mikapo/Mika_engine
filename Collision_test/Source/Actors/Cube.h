#pragma once

#include "Objects/Actor.h"

namespace MEngine
{
    class Mesh_component;
}

class Cube : public MEngine::Actor
{
    GENERATED_BODY(Cube)

public:
    void initialize() override;
    void set_color(glm::vec4 color);

private:
    MEngine::Mesh_component* m_mesh_component = nullptr;
};
