#include "fps_calculator.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

float FpsCalculator::delta = 0;
float FpsCalculator::lastFrame = 0;

float FpsCalculator::getDelta() {
	return delta;
}

void FpsCalculator::calcDelta()
{
	float currentFrame = glfwGetTime();
	delta = currentFrame - lastFrame;
	lastFrame = currentFrame;
}
