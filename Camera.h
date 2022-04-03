#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
	static float speed;
	static float sensitivity;

	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;

	float yaw;
	float pitch;

	Camera(const Camera&) = delete;
	Camera& operator = (const Camera& c) = delete;

	Camera();
	static Camera instance;

public:
	static Camera& get();
	void moveForwards(float deltaTime);
	void moveBackwards(float deltaTime);
	void moveLeft(float deltaTime);
	void moveRight(float deltaTime);
	void turn(float xoffset, float yoffset);

	glm::mat4 getViewMatrix();

};

