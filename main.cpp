#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "south_african_flag/south_african_flag.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);
std::string read_all_lines(const char* source) noexcept(false);
GLuint create_shader_program();
bool checkShaderCompilation(GLuint shaderID);
bool compile_and_attach_shader(GLuint programID, unsigned int type, const char* path);

int main(int argc, char** argv) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);

	if (window == nullptr) {
		std::cout << "failed to create window" << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "failed to initialise GLAD" << std::endl;
		return 1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glClearColor(1.0f, 1.0f, 0.7f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint green_background_vao = green_background();
	GLuint golden_triangle_vao = golden_triangle();
	GLuint black_triangle_vao = black_triangle();

	GLuint program = create_shader_program();
	glUseProgram(program);

	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(green_background_vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);

		glBindVertexArray(golden_triangle_vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(black_triangle_vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(program);

	glfwTerminate();

	return 0;
}

std::string read_all_lines(const char* source) noexcept(false) {
	std::stringstream ss;
	std::ifstream file(source);

	if (!file.is_open()) {
		throw std::string("could not open ") + source;
	}

	ss << file.rdbuf();
	file.close();
	return ss.str();
}

bool compile_and_attach_shader(GLuint programID, unsigned int type, const char* path) {
	std::string source = read_all_lines(path);
	const GLchar* sourceCStr = source.c_str();

	GLuint shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &sourceCStr, NULL);
	glCompileShader(shaderID);

	if (!checkShaderCompilation(shaderID)) {
		glDeleteShader(shaderID);
		std::cerr << std::string("could not compile shader");
		return false;
	}

	glAttachShader(programID, shaderID);

	return true;
}

GLuint create_shader_program() {
	GLuint programID = glCreateProgram();

	bool status = true;
	status = status && compile_and_attach_shader(programID, GL_VERTEX_SHADER, "res\\vertex_shader.glsl");
	status = status && compile_and_attach_shader(programID, GL_FRAGMENT_SHADER, "res\\fragment_shader.glsl");

	if (!status) {
		glDeleteProgram(programID);
		return 0;
	}

	glLinkProgram(programID);

	return programID;
}

bool checkShaderCompilation(GLuint shaderID) {
	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (success) {
		return true;
	}

	GLint infoLogLength;
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

	std::vector<GLchar> infoLog(infoLogLength);
	glGetShaderInfoLog(shaderID, infoLogLength, nullptr, infoLog.data());
	std::cerr << "shader compile error:\n" << infoLog.data() << "\n";

	return false;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
