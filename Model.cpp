#include <iostream>
#include "Model.h"

Model::Model(const std::string& path) {
	LoadModel(path);
}

void Model::Draw() {
	for (auto mesh : meshes) {
		mesh->Draw();
	}
}

void Model::LoadModel(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, 
		aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << "\n";
		return;
	}
	for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
		meshes.push_back(ProcessMesh(scene->mMeshes[i], scene));
	}
}

Mesh* Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<float> vertices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		vertices.push_back(mesh->mVertices[i].x);
		vertices.push_back(mesh->mVertices[i].y);
		vertices.push_back(mesh->mVertices[i].z);
	}

	return new Mesh(vertices.data(), vertices.size() * sizeof(float));
}
