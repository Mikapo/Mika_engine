#include "Model_loader.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <exception>
#include <span>
#include <vector>

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices)

std::unique_ptr<OpenGL::Buffers> OpenGL::Model_loader::load(std::string_view file_path, size_t mesh_index)
{
    Assimp::Importer importer;
    const aiScene* const scene = importer.ReadFile(file_path.data(), ASSIMP_LOAD_FLAGS);

    if (scene == nullptr)
        throw std::invalid_argument("Failed to open model file");

    return load_mesh_from_scene(scene, mesh_index);
}

std::unique_ptr<OpenGL::Buffers> OpenGL::Model_loader::load_mesh_from_scene(const aiScene* scene, size_t index)
{
    if (scene == nullptr)
        throw std::invalid_argument("Scene was null");

    const std::span meshes = {scene->mMeshes, scene->mNumMeshes};

    if (index >= meshes.size())
        throw std::invalid_argument("There is no mesh with spesified index");

    aiMesh* mesh = meshes[index];

    std::vector<float> vertices;
    get_vertices(mesh, vertices);

    std::vector<uint32_t> indices;
    get_indices(mesh, indices);

    Vertex_buffer_layout layout = create_layout();

    return std::make_unique<Buffers>(std::move(vertices), std::move(indices), std::move(layout));
}

void OpenGL::Model_loader::get_indices(const aiMesh* mesh, std::vector<uint32_t>& out_vector)
{
    if (mesh == nullptr)
        throw std::invalid_argument("Mesh was null");

    const std::span faces = {mesh->mFaces, mesh->mNumFaces};

    constexpr size_t out_vector_reserve_multiplier = 10;
    out_vector.reserve(faces.size() * out_vector_reserve_multiplier);

    for (const aiFace& face : faces)
    {
        const std::span indices = {face.mIndices, face.mNumIndices};

        for (const uint32_t indice : indices)
            out_vector.push_back(indice);
    }
}

OpenGL::Vertex_buffer_layout OpenGL::Model_loader::create_layout()
{
    Vertex_buffer_layout layout;
    layout.push_float(3);
    layout.push_float(3);
    layout.push_float(2);

    return layout;
}

void OpenGL::Model_loader::get_vertices(aiMesh* mesh, std::vector<float>& out_vector)
{
    if (mesh == nullptr)
        throw std::invalid_argument("Mesh is null");

    if (!mesh->HasNormals())
        throw std::invalid_argument("Mesh is missing normals");

    const std::span vertices = {mesh->mVertices, mesh->mNumVertices};
    const std::span normals = {mesh->mNormals, mesh->mNumVertices};

    std::span<aiVector3D, std::dynamic_extent> texture_coordinates;

    if (mesh->HasTextureCoords(0))
        texture_coordinates = {mesh->mTextureCoords[0], vertices.size()};

    constexpr size_t values_per_vertice = 8;
    out_vector.reserve(vertices.size() * values_per_vertice);

    // Pushes vertices to vector in spesific format
    // 1. location
    // 2. normals
    // 3. tex_coords
    for (int32_t i = 0; i < vertices.size(); i++)
    {
        out_vector.push_back(vertices[i].x);
        out_vector.push_back(vertices[i].y);
        out_vector.push_back(vertices[i].z);

        out_vector.push_back(normals[i].x);
        out_vector.push_back(normals[i].y);
        out_vector.push_back(normals[i].z);

        // Check if there is any texture coordinates for this vertice
        if (i < texture_coordinates.size())
        {
            out_vector.push_back(texture_coordinates[i].x);
            out_vector.push_back(texture_coordinates[i].y);
        }
        else
        {
            out_vector.push_back(0.0F);
            out_vector.push_back(0.0F);
        }
    }
}
