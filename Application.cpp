#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "ShaderSources.h"
#include "Application.h"

constexpr int Screen_Width = 800;
constexpr int Screen_Height = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void Application::InitializeWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(Screen_Width, Screen_Height, "3D Renderer", nullptr, nullptr);
	if (!window) {
		std::cout << "Failed to initialize window" << "\n";
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << "\n";
		return;
	}

	glViewport(0, 0, Screen_Width, Screen_Height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	ShaderSources src;
	shader = new Shader(src.vertexShaderSource, src.fragmentShaderSource);
}

void Application::Run()
{
	while (!glfwWindowShouldClose(window)) {
		processInput(window);


		shader->Use();
		glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return;
}

void Application::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
