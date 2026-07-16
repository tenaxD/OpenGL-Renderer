#pragma once
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include "Shader.h"

class Application {
public:
	void InitializeWindow();
	void Run();
	void processInput(GLFWwindow* window);
	glm::vec4 bgColor = { 0.61f, 0.61f, 0.61f, 1.0f };
private:
	GLFWwindow* window = nullptr;
	Shader* shader = nullptr;
};
