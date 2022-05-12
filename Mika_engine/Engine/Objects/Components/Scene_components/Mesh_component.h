#pragma once

#include "Scene_component.h"
#include "glm/mat4x4.hpp"
#include "Utility/Frame_data.h"
#include <string_view>
#include <optional>

class Mesh;
class Shader;
class Material;
class Mesh_component : public Scene_component
{
public:
	void update(float deltatime) override;
	void initialize() override;
	void load_mesh_from_file(std::string_view file, int32_t mesh_index = 0);
	void set_material_to_current_mesh(const Material& material);
	void get_owned_objects(std::vector<Object*>& out_array) override;
	std::optional<Mesh_data> get_mesh_data();
	
private:
	Mesh* m_mesh = nullptr;
};

