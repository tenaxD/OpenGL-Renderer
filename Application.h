#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include <vector>
#include "Mesh.h"
#include "Model.h"
#include "Camera.h"

class Application {
public:
	void InitializeWindow();
	void Run();
	void processInput(GLFWwindow* window, float deltaTime);
	void mouseCallback(double xPos, double yPos);
	static void StaticMouseCallback(GLFWwindow* window, double xPos, double yPos);
	glm::vec4 bgColor = { 0.61f, 0.61f, 0.61f, 1.0f };
private:
	Camera* camera = nullptr;
	float lastFrame = 0.0f;
	float lastX{ 400.0f }, lastY{ 300.0f };
	bool firstMouse = true;
	GLFWwindow* window = nullptr;
	Shader* shader = nullptr;
	std::vector<Model*> models;
	std::vector<Mesh*> meshes;

	std::vector<glm::vec3> positions = {
			glm::vec3(0.0f, 0.0f,  0.0f),
			glm::vec3(2.0f, 0.0f,  0.0f),
			glm::vec3(-2.0f, 0.0f,  0.0f)
	};
	std::vector<float> modelScales = { 0.01f, 1.0f };
};
