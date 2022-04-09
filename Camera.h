#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "game/entities/entity.h"

class Camera: public Entity
{
	static float speed;
	static float sensitivity;

	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;

	float yaw;
	float pitch;

	bool movingForwards;
	bool movingBackwards;
	bool movingLeft;
	bool movingRight;

	void turn(float xoffset, float yoffset);

public:
	Camera();

	void moveForwards(float deltaTime);
	void moveBackwards(float deltaTime);
	void moveLeft(float deltaTime);
	void moveRight(float deltaTime);

	void handleKeyboard(int key, int scancode, int action, int mods);
	void handleMouse(double xpos, double ypos);

	void update(float deltaTime);

	const glm::vec3& getPosition();
	glm::mat4 getViewMatrix();

};

