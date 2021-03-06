#pragma once

#include "Scene_component.h"
#include "glm/mat4x4.hpp"
#include "Datatypes/Frame_data.h"
#include <string_view>
#include <optional>

class Mesh;
class Shader;
class Material;
class Mesh_component : public Scene_component
{
    GENERATED_BODY(Mesh_component)

public:
    void initialize() override;
    void set_mesh(std::shared_ptr<Mesh> mesh) noexcept;
    void set_material(const Material& material) noexcept;
    Material get_material() const noexcept;

	std::optional<Mesh_data> get_mesh_data() const noexcept;
	
private:
	std::shared_ptr<Mesh> m_mesh = nullptr;
    Material m_material;
};

