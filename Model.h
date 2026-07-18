#pragma once
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

class Model {
public:
	Model(const std::string& path);
	void Draw();
private:
	std::vector<Mesh*> meshes;
	void LoadModel(const std::string& path);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
};