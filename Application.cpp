#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "ShaderSources.h"
#include "Primitives.h"
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

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, Screen_Width, Screen_Height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	ShaderSources src;
	shader = new Shader(src.vertexShaderSource, src.fragmentShaderSource);

	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetWindowUserPointer(window, this);
	glfwSetCursorPosCallback(window, StaticMouseCallback);

	models.push_back(new Model("C:/Users/Admin/Downloads/UE4_Mannequin.FBX"));
	models.push_back(new Model("C:/Users/Admin/Desktop/Stalker.fbx"));


	/*meshes.push_back(Primitives::CreateTriangle());
	meshes.push_back(Primitives::CreateCube());*/

}

void Application::Run()
{
	while (!glfwWindowShouldClose(window)) {
		float currentFrame = static_cast<float>(glfwGetTime());
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window, deltaTime);

		//rendering
		glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader->Use();

		//primitives
		shader->SetBool("hasTexture", false);
		shader->SetMat4("view", camera->GetViewMatrix());
		shader->SetMat4("projection", camera->GetProjectionMatrix(800.0f, 600.0f));
		for (size_t i{}; i < meshes.size(); i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, positions[i]);
			shader->SetMat4("model", model);
			meshes[i]->Draw();
		}
		//rendering imported obj, fbx etc.
		for (size_t i{}; i < models.size(); i++) {
			shader->SetBool("hasTexture", models[i]->HasTextures());
			glm::mat4 modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::rotate(modelMatrix, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(modelScales[i], modelScales[i], modelScales[i]));
			modelMatrix = glm::translate(modelMatrix, positions[i]);
			shader->SetMat4("model", modelMatrix);
			models[i]->Draw();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return;
}

void Application::processInput(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	camera->ProcessKeyboard(deltaTime,
		glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS,
		glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS,
		glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS,
		glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS,
		glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS,
		glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS,
		glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS
	);
}

void Application::mouseCallback(double xPos, double yPos)
{
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;

	camera->ProcessMouse(xOffset, yOffset);
}

void Application::StaticMouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	Application* app = (Application*)glfwGetWindowUserPointer(window);
	app->mouseCallback(xPos, yPos);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
