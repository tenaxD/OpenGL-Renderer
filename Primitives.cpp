#include "Primitives.h"

Mesh* Primitives::CreateTriangle()
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	return new Mesh(vertices, sizeof(vertices));
}

Mesh* Primitives::CreateCube()
{
	float vertices[] = {
		//front
		-0.5f, -0.5f, 0.5f,  0.5f,-0.5f,0.5f,  0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,   -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f,
		//back
		-0.5f, -0.5f, -0.5f,  0.5f,-0.5f,-0.5f,  0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,   -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
		//left
		-0.5f,-0.5f,-0.5f,  -0.5f,-0.5f, 0.5f,  -0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,  -0.5f, 0.5f,-0.5f,  -0.5f,-0.5f,-0.5f,
		// right
		 0.5f,-0.5f,-0.5f,   0.5f,-0.5f, 0.5f,   0.5f, 0.5f, 0.5f,
		 0.5f, 0.5f, 0.5f,   0.5f, 0.5f,-0.5f,   0.5f,-0.5f,-0.5f,
		 // top
		 -0.5f, 0.5f, 0.5f,   0.5f, 0.5f, 0.5f,   0.5f, 0.5f,-0.5f,
		  0.5f, 0.5f,-0.5f,  -0.5f, 0.5f,-0.5f,  -0.5f, 0.5f, 0.5f,
		  // down
		  -0.5f,-0.5f, 0.5f,   0.5f,-0.5f, 0.5f,   0.5f,-0.5f,-0.5f,
		   0.5f,-0.5f,-0.5f,  -0.5f,-0.5f,-0.5f,  -0.5f,-0.5f, 0.5f,
	};
	return new Mesh(vertices, sizeof(vertices));
}
