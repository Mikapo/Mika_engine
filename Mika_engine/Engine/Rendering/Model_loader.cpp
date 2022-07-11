#include "Model_loader.h"

#include <assimp/Importer.hpp>   
#include <assimp/postprocess.h> 
#include <assimp/scene.h>      
#include <vector>
#include <exception>
#include "gsl/span"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals |  aiProcess_JoinIdenticalVertices )
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

std::unique_ptr<Buffers> Model_loader::load(std::string_view file_path, int32_t mesh_index)
{
	return load_buffer(file_path, mesh_index);
}

std::unique_ptr<Buffers> Model_loader::load_buffer(std::string_view file_path, int32_t mesh_index)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(file_path.data(), ASSIMP_LOAD_FLAGS);

	if (!scene)
		throw std::invalid_argument("model file not found");
	
	return load_mesh_from_scene(file_path, scene, mesh_index);
}

std::unique_ptr<Buffers> Model_loader::load_mesh_from_scene(std::string_view path, const aiScene* scene, int32_t index)
{
    if (!scene)
        throw std::invalid_argument("scene was null");

	const gsl::span meshes = {scene->mMeshes, scene->mNumMeshes};
    aiMesh* mesh = gsl::at(meshes, 0);

	std::vector<float> vertices;
	get_vertices(mesh, vertices);

	std::vector<uint32_t> indices;
	get_indices(mesh, indices);

	Vertex_buffer_layout layout;
	layout.push<float>(3);
	layout.push<float>(3);
	layout.push<float>(2);

    return std::make_unique<Buffers>(std::move(vertices), std::move(indices), layout);
}

void Model_loader::get_indices(const aiMesh* mesh, std::vector<uint32_t>& out_vector)
{
    if (!mesh)
        throw std::invalid_argument("mesh was null");

    const gsl::span faces = {mesh->mFaces, mesh->mNumFaces};
    out_vector.reserve(faces.size() * 10);

	for (const aiFace& face : faces)
	{
        const gsl::span indices = {face.mIndices, face.mNumIndices};

		for (const uint32_t indice : indices)
			out_vector.push_back(indice);
	}
}

void Model_loader::get_vertices(aiMesh* mesh, std::vector<float>& out_vector)
{
    if (!mesh)
        throw std::invalid_argument("mesh is null");

    if (!mesh->HasNormals())
        throw std::invalid_argument("mesh is missing normals");


    const gsl::span vertices = {mesh->mVertices, mesh->mNumVertices};
    const gsl::span normals = {mesh->mNormals, mesh->mNumVertices};

	gsl::span<aiVector3D, std::dynamic_extent> texture_coordinates;
	
	if (mesh->HasTextureCoords(0))
		texture_coordinates = {mesh->mTextureCoords[0], vertices.size()};

	out_vector.reserve(vertices.size() * 8);

	for (int32_t i = 0; i < vertices.size(); i++)
	{
		out_vector.push_back(gsl::at(vertices, i).x);
        out_vector.push_back(gsl::at(vertices, i).y);
        out_vector.push_back(gsl::at(vertices, i).z);

		out_vector.push_back(gsl::at(normals, i).x);
        out_vector.push_back(gsl::at(normals, i).y);
        out_vector.push_back(gsl::at(normals, i).z);

		if (texture_coordinates.size() < i)
		{
            out_vector.push_back(gsl::at(texture_coordinates, i).x);
            out_vector.push_back(gsl::at(texture_coordinates, i).y);
		}
		else
        {
            out_vector.push_back(0.0f);
            out_vector.push_back(0.0f);
		}
	}
}

