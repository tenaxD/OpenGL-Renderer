#pragma once
class Mesh {
public:
	Mesh(float vertices[], unsigned int size, unsigned int textureID = 0);
	void Draw();
	~Mesh();
private:
	unsigned int VAO, VBO;
	unsigned int vertexCount;
	unsigned int textureID;
};