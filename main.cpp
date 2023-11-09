#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);
std::string read_all_lines(const char* source) noexcept(false);
GLuint create_shader_program();

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

	glClearColor(0.5f, 0.25f, 0.0f, 1.0f);

	GLuint program = create_shader_program();

	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

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

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
