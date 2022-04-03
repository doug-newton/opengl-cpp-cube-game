#include "Camera.h"
#include <math.h>

float Camera::speed = 2.5f;
float Camera::sensitivity = 0.1f;
Camera Camera::instance;

Camera& Camera::get()
{
	return instance;
}

Camera::Camera()
	:
	pos(-3.0f, 1.0f, 0.0f),
	front(0.0f, 0.0f, -1.0f),
	up(0.0f, 1.0f, 0.0f),
    yaw(-90.0f),
    pitch(0.0f)
{
}

void Camera::moveForwards(float deltaTime)
{
	pos += speed * deltaTime * front;
}

void Camera::moveBackwards(float deltaTime)
{
	pos -= speed * deltaTime * front;
}

void Camera::moveLeft(float deltaTime)
{
	pos -= glm::normalize(glm::cross(front, up)) * speed * deltaTime;
}

void Camera::moveRight(float deltaTime)
{
	pos += glm::normalize(glm::cross(front, up)) * speed * deltaTime;
}

void Camera::turn(float xoffset, float yoffset) {
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    pitch += yoffset;
    yaw = std::fmod(yaw + xoffset, 360.0f);

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);
}

const glm::vec3& Camera::getPosition() {
    return pos;
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(pos, pos + front, up);
}
