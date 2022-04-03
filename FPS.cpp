#include "FPS.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

float FPS::delta = 0;
float FPS::lastFrame = 0;

float FPS::getDelta() {
	return delta;
}

void FPS::calcDelta()
{
	float currentFrame = glfwGetTime();
	delta = currentFrame - lastFrame;
	lastFrame = currentFrame;
}
