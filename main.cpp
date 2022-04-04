#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "textures.h"
#include "vaos.h"
#include "callbacks.h"
#include "gl_util.h"
#include "FPS.h"
#include "Camera.h"
#include "game/shaders/simple/simple_shader.h"
#include "game/shaders/lighting/lighting_shader.h"

int glMain();

int main() {
	return glMain();
}

int glMain()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(600, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 600, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	GLuint texture0 = loadJpg("container.jpg");
	GLuint texture1 = loadPng("awesomeface.png");
	GLuint vao = createCubeWithNormals();
	GLuint lightVao = createLightVao();

	SimpleShader simpleShader;
	LightingShader lightingShader;

	ShaderMaterial material(
		glm::vec3(1.0f, 0.5f, 0.31f),
		glm::vec3(1.0f, 0.5f, 0.31f),
		glm::vec3(0.5f, 0.5f, 0.9f),
		32.0f);

	ShaderLight light(
		glm::vec3(-3.0f, 5.0f, -3.0f),
		glm::vec3(0.2f, 0.2f, 0.2f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 1.0f, 1.0f)
	);

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 600.0f / 600.0f, 0.1f, 100.0f);
	glm::vec3 position(0.0f, 0.0f, -3.0f);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		FPS::calcDelta();
		float deltaTime = FPS::getDelta();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = Camera::get().getViewMatrix();

		//	for the light itself, use the simple shader (don't apply lighting to it)

		simpleShader.use();
		simpleShader.setProjection(projection);
		simpleShader.setView(view);

		glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, light.position);
		lightModel = glm::scale(lightModel, glm::vec3(0.2f));

		simpleShader.setObjectColor(lightColor);

		glBindVertexArray(lightVao);
		simpleShader.setModel(lightModel);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//	for the rest of the objects, use the lighting shader (apply lighting)

		lightingShader.use();
		lightingShader.setProjection(projection);
		lightingShader.setView(view);

		lightingShader.setLight(light);
		lightingShader.setMaterial(material);
		lightingShader.setViewPos(Camera::get().getPosition());

		//	draw all entities except the light

		glBindVertexArray(vao);
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, position);
		transform = glm::scale(transform, glm::vec3(3.0f, 3.0f, 3.0f));
		lightingShader.setModel(transform);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}
