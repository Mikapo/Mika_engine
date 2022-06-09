#include "Model_loader.h"

#include <assimp/Importer.hpp>   
#include <assimp/postprocess.h> 
#include <assimp/scene.h>      
#include <iostream>
#include <vector>
#include <exception>

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
	auto mesh = scene->mMeshes[index];

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
	int32_t face_amount = mesh->mNumFaces;
	out_vector.reserve(face_amount * 10);

	for (int32_t a = 0; a < face_amount; a++)
	{
		auto face = mesh->mFaces[a];
		for (uint32_t b = 0; b < face.mNumIndices; b++)
		{
			out_vector.push_back(face.mIndices[b]);
		}
	}
}

void Model_loader::get_vertices(aiMesh* mesh, std::vector<float>& out_vector)
{
	auto vertices = mesh->mVertices;
	auto normals = mesh->mNormals;
	auto texture_cordinates = mesh->mTextureCoords;
	bool has_texture_cordinates = mesh->HasTextureCoords(0);
	int32_t number_of_vertices = mesh->mNumVertices;

	out_vector.reserve(number_of_vertices * 8);

	for (int32_t i = 0; i < number_of_vertices; i++)
	{
		out_vector.push_back(vertices[i].x);
		out_vector.push_back(vertices[i].y);
		out_vector.push_back(vertices[i].z);

		out_vector.push_back(normals[i].x);
		out_vector.push_back(normals[i].y);
		out_vector.push_back(normals[i].z);

		aiVector3D texture_coordinate = { 0.0f, 0.0f, 0.0f };
		if (has_texture_cordinates)
			texture_coordinate = texture_cordinates[0][i];

		out_vector.push_back(texture_coordinate.x);
		out_vector.push_back(texture_coordinate.y);
	}
}

