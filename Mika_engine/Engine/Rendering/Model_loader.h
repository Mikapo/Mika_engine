#pragma once

#include "GL/glew.h"

#include <array>
#include <memory>
#include <vector>
#include <string>
#include <optional>
#include <future>

#include "Rendering/Buffers/Buffers.h"

struct aiMesh;
struct aiScene;

class Model_loader
{
public:
	static std::shared_ptr<Buffers> load(std::string_view file_path, int32_t mesh_index);

private:
	static std::shared_ptr<Buffers> load_buffer(std::string_view file_path, int32_t mesh_index = 0);
	static std::shared_ptr<Buffers> load_mesh_from_scene(std::string_view path, const aiScene* scene, int32_t index);
	static void get_vertices(aiMesh* mesh, std::vector<float>& out_vecto);
	static void get_indices(const aiMesh* mesh, std::vector<uint32_t>& out_vector);

};

