#pragma once

#include "Buffers/Buffers.h"
#include <array>
#include <future>
#include <memory>
#include <optional>
#include <string>
#include <vector>

struct aiMesh;
struct aiScene;
namespace OpenGL
{
    class Model_loader
    {
    public:
        Model_loader() = delete;

        [[nodiscard]] static std::unique_ptr<Buffers> load(std::string_view file_path, size_t mesh_index);

    private:
        [[nodiscard]] static std::unique_ptr<Buffers> load_mesh_from_scene(const aiScene* scene, size_t index);
        static void get_vertices(aiMesh* mesh, std::vector<float>& out_vecto);
        static void get_indices(const aiMesh* mesh, std::vector<uint32_t>& out_vector);
        [[nodiscard]] static Vertex_buffer_layout create_layout();
    };

} // namespace OpenGL
