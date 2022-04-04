#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shaders.h"
#include "textures.h"
#include "vaos.h"
#include "callbacks.h"
#include "gl_util.h"
#include "FPS.h"
#include "Camera.h"

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

	GLuint program = createShaderProgram();
	GLuint lightingProgram = createLightingShader();
	GLuint texture0 = loadJpg("container.jpg");
	GLuint texture1 = loadPng("awesomeface.png");
	GLuint vao = createCubeWithNormals();
	GLuint lightVao = createLightVao();

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 600.0f / 600.0f, 0.1f, 100.0f);

	float positions[] = {
		 0.0f,  0.0f, -3.0f,
	};

	float colors[] = {
		//	1.0f, 0.0f, 0.0f, //red
		//	0.0f, 1.0f, 0.0f, //green
		//	0.0f, 0.0f, 1.0f, //blue
		//	0.0f, 1.0f, 1.0f, //cyan
		1.0f, 0.0f, 1.0f, //magenta
		//	1.0f, 1.0f, 0.0f, //yellow
	};

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		FPS::calcDelta();
		float deltaTime = FPS::getDelta();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = Camera::get().getViewMatrix();

		//	for the light itself, use the original shader (don't apply lighting to it)

		glUseProgram(program);
		int modelLocation = glGetUniformLocation(program, "model");
		int viewLocation = glGetUniformLocation(program, "view");
		int projectionLocation = glGetUniformLocation(program, "projection");
		int objectColorLocation = glGetUniformLocation(program, "objectColor");

		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

		glm::vec3 lightPos(-3.0f,  5.0f, -3.0f);
		glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);
		lightModel = glm::scale(lightModel, glm::vec3(0.2f));
		glUniform3f(objectColorLocation, lightColor.x, lightColor.y, lightColor.z);
		glBindVertexArray(lightVao);
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(lightModel));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//	for the rest of the objects, use the lighting shader (apply lighting)

		glUseProgram(lightingProgram);
		modelLocation = glGetUniformLocation(lightingProgram, "model");
		viewLocation = glGetUniformLocation(lightingProgram, "view");
		projectionLocation = glGetUniformLocation(lightingProgram, "projection");
		objectColorLocation = glGetUniformLocation(lightingProgram, "objectColor");
		int viewPosLocation = glGetUniformLocation(lightingProgram, "viewPos");

		int lightPositionLocation = glGetUniformLocation(lightingProgram, "light.position");
		int lightAmbientLocation = glGetUniformLocation(lightingProgram, "light.ambient");
		int lightDiffuseLocation = glGetUniformLocation(lightingProgram, "light.diffuse");
		int lightSpecularLocation = glGetUniformLocation(lightingProgram, "light.specular");

		int materialAmbientLocation = glGetUniformLocation(lightingProgram, "material.ambient");
		int materialDiffuseLocation = glGetUniformLocation(lightingProgram, "material.diffuse");
		int materialSpecularLocation = glGetUniformLocation(lightingProgram, "material.specular");
		int materialShininessLocation = glGetUniformLocation(lightingProgram, "material.shininess");

		glUniform3f(materialAmbientLocation, 1.0f, 0.5f, 0.31f);
		glUniform3f(materialDiffuseLocation, 1.0f, 0.5f, 0.31f);
		glUniform3f(materialSpecularLocation, 0.5f, 0.5f, 0.9f);
		glUniform1f(materialShininessLocation, 32.0f);

		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

		glm::vec3 viewPos = Camera::get().getPosition();
		glUniform3f(viewPosLocation, viewPos.x, viewPos.y, viewPos.z);

		glUniform3f(lightPositionLocation, lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(lightAmbientLocation, 0.2f, 0.2f, 0.2f);
		glUniform3f(lightDiffuseLocation, 0.5f, 0.5f, 0.5f);
		glUniform3f(lightSpecularLocation, 1.0f, 1.0f, 1.0f);

		glBindVertexArray(vao);
		for (int i = 0; i < sizeof(positions) / sizeof(float) / 3; i++) {
			glm::mat4 transform = glm::mat4(1.0f);

			float x = positions[i * 3 + 0];
			float y = positions[i * 3 + 1];
			float z = positions[i * 3 + 2];

			float r = colors[i * 3 + 0];
			float g = colors[i * 3 + 1];
			float b = colors[i * 3 + 2];

			transform = glm::translate(transform, glm::vec3(
				x, y, z
			));
			transform = glm::scale(transform, glm::vec3(3.0f, 3.0f, 3.0f));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(transform));
			glUniform3f(objectColorLocation, r, g, b);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}
