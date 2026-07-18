#include "Camera.h"

Camera::Camera(glm::vec3 position)
{
	this->position = position;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetProjectionMatrix(float screenWidth, float screenHeight)
{
	return glm::perspective(glm::radians(fov), screenWidth / screenHeight, 0.1f, 100.0f);
}

void Camera::ProcessKeyboard(float deltaTime, bool forward, bool backward, bool left, bool right, bool moveUp, bool moveDown, bool sprint)
{
	float velocity = speed * deltaTime;
	if (sprint) velocity *= 3.0f;
	if (forward) position += front * velocity;
	if (backward) position -= front * velocity;
	glm::vec3 right_dir = glm::normalize(glm::cross(front, up));
	if (left)  position -= right_dir * velocity;
	if (right) position += right_dir * velocity;
	if (moveUp) position += up * velocity;
	if (moveDown) position -= up * velocity;
}

void Camera::ProcessMouse(float xOffset, float yOffset)
{
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(direction);
}
