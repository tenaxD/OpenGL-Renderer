#pragma once
class Mesh {
public:
	Mesh(float vertices[], unsigned int size);
	void Draw();
	~Mesh();
private:
	unsigned int VAO, VBO;
	unsigned int vertexCount;
};