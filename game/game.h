#pragma once
#include "entities/entity.h"
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../textures.h"
#include "../vaos.h"
#include "../Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderer.h"

#include "shaders/lighting/shader_light.h"
#include "shaders/lighting/shader_material.h"

#include "entities/light.h"
#include "entities/block.h"

class Game: Entity {

	std::vector<Entity*> entities;

	GLuint texture0 = loadJpg("container.jpg");
	GLuint texture1 = loadPng("awesomeface.png");

public:

	static Game* instance;

	GLFWwindow* window;

	glm::mat4 projection;

	Camera* camera;
	Light* light;
	Block* block;

	Game();
	~Game();

	bool init();
	void update(float deltaTime = 1);
	void render();
	void handleKeyboard(int key, int scancode, int action, int mods);
	void handleMouse(double xpos, double ypos);

	void addEntity(Entity* entity);

	void setCallbacks();
};
