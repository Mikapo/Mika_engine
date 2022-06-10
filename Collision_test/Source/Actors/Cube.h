#pragma once

#include "Objects/Actor.h"

class Mesh_component;
class Cube : public Actor
{
    GENERATED_BODY(Cube)

public:
    void initialize() override;
    void set_color(glm::vec4 color);

private:
    Mesh_component* m_mesh_component = nullptr;
};
