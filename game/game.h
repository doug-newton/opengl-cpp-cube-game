#pragma once
#include "entities/entity_group.h"
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../textures.h"
#include "meshes/vaos.h"
#include "entities/Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "fps_calculator.h"

#include "renderer.h"

#include "shaders/lighting/shader_light.h"
#include "shaders/lighting/shader_material.h"

#include "entities/light.h"
#include "entities/block.h"
#include "entities/tilemap.h"

class Game: public EntityGroup {

private:

	GLFWwindow* window;
	Camera* camera;
	Light* light;
	Block* block;

public:

	static Game* instance;

	Game();

	void mainLoop();

	bool init();
	void update();
	void render();
	void setCallbacks();

	void handleWindowSizeChange(int w, int h);
};
