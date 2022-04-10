#pragma once
#include "entities/entity_group.h"
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
#include "entities/tilemap.h"

class Game: public EntityGroup {

public:

	static Game* instance;

	GLFWwindow* window;

	glm::mat4 projection;

	Camera* camera;
	Light* light;

	Game();

	bool init();
	void render();
	void setCallbacks();
};
