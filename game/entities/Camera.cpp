#include "Camera.h"
#include <math.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include "../../FPS.h"

float Camera::speed = 2.5f;
float Camera::sensitivity = 0.1f;

Camera::Camera(int windowWidth, int windowHeight)
	:
	windowWidth(windowWidth),
	windowHeight(windowHeight),
	pos(1.60671f, 3.17601f, 11.4618f),
	front(-0.020663f, -0.161604f, -0.986639f),
	up(0.0f, 1.0f, 0.0f),
    yaw(-91.1998f),
    pitch(-9.29999f),
	movingForwards(false),
	movingBackwards(false),
	movingLeft(false),
	movingRight(false)
{
}

void Camera::handleKeyboard(int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
		case GLFW_KEY_W:
			this->movingForwards = true;
			break;
		case GLFW_KEY_S:
			this->movingBackwards = true;
			break;
		case GLFW_KEY_A:
			this->movingLeft = true;
			break;
		case GLFW_KEY_D:
			this->movingRight = true;
			break;
		}
	}
	else if (action == GLFW_RELEASE) {
        switch (key) {
		case GLFW_KEY_W:
			this->movingForwards = false;
			break;
		case GLFW_KEY_S:
			this->movingBackwards = false;
			break;
		case GLFW_KEY_A:
			this->movingLeft = false;
			break;
		case GLFW_KEY_D:
			this->movingRight = false;
			break;
		}
	}
}

void Camera::update(float deltaTime) {
	if (movingForwards) moveForwards(deltaTime);
	else if (movingBackwards) moveBackwards(deltaTime);
	if (movingLeft) moveLeft(deltaTime);
	else if (movingRight) moveRight(deltaTime);

	/*
	std::cout 
		<< "pos: (" << pos.x << "f, " << pos.y << "f, " << pos.z << "f), "
		<< "front: (" << front.x << "f, " << front.y << "f, " << front.z << "f), "
		<< "up: (" << up.x << "f, " << up.y << "f, " << up.z << "f), "
		<< "yaw: " << yaw << "f, pitch: " << pitch << "f" << std::endl;
	*/
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

glm::mat4 Camera::getProjectionMatrix() {
	return glm::perspective(glm::radians(45.0f), (float)windowWidth/windowHeight, 0.1f, 100.0f);
}

void Camera::handleMouse(double xpos, double ypos) {
    static bool firstMouse = true;
    static double lastX;
    static double lastY;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
		return;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

	turn(xoffset, yoffset);
}

void Camera::setWindowDimensions(int w, int h) {
	windowWidth = w;
	windowHeight = h;
}