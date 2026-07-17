#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera(glm::vec3 position);
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(float screenWidth, float screenHeight);
	void ProcessKeyboard(float deltaTime, bool forward, bool backward, bool left, bool right);
	void ProcessMouse(float xOffset, float yOffset);

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;

	float yaw = -90.0f;
	float pitch = 0.0f;
	float speed = 2.5f;
	float sensitivity = 0.1f;
	float fov = 45.0f;
};