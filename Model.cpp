#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
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

Mesh* Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<float> vertices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);

        if (mesh->mTextureCoords[0]) {
            vertices.push_back(mesh->mTextureCoords[0][i].x);
            vertices.push_back(mesh->mTextureCoords[0][i].y);
        }
        else {
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
        }
    }

    unsigned int textureID = 0;
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        aiString texPath;
        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texPath) == AI_SUCCESS) {
            const aiTexture* embeddedTex = scene->GetEmbeddedTexture(texPath.C_Str());
            if (embeddedTex) {
                textureID = LoadEmbeddedTexture(embeddedTex);
                hasTextures = true;
            }
        }
    }

    return new Mesh(vertices.data(), vertices.size() * sizeof(float), textureID, true);
}


unsigned int Model::LoadTexture(const std::string& path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (data) {
        GLenum format = channels == 4 ? GL_RGBA : GL_RGB;
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture: " << path << "\n";
    }

    stbi_image_free(data);
    return textureID;
}

unsigned int Model::LoadEmbeddedTexture(const aiTexture* texture)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, channels;
    unsigned char* data;

    if (texture->mHeight == 0) {
        data = stbi_load_from_memory(
            reinterpret_cast<unsigned char*>(texture->pcData),
            texture->mWidth, &width, &height, &channels, 0
        );
    }
    else {
        data = reinterpret_cast<unsigned char*>(texture->pcData);
        width = texture->mWidth;
        height = texture->mHeight;
        channels = 4;
    }

    if (data) {
        GLenum format = channels == 4 ? GL_RGBA : GL_RGB;
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        if (texture->mHeight == 0) stbi_image_free(data);
    }

    return textureID;
}
