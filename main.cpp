#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "textures.h"
#include "vaos.h"
#include "gl_util.h"
#include "FPS.h"
#include <vector>
#include "game/game.h"

int glMain();

int main() {
	return glMain();
}

int glMain()
{
	Game game;

	if (!game.init())
		return -1;

	game.setCallbacks();

	while (!glfwWindowShouldClose(game.window)) {
		FPS::calcDelta();
		float deltaTime = FPS::getDelta();

		game.update(deltaTime);
		game.render();

		glfwPollEvents();
		glfwSwapBuffers(game.window);
	}

	glfwTerminate();

	return 0;
}
