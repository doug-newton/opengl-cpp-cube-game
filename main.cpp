#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);
std::string read_all_lines(const char* source) noexcept(false);
GLuint create_shader_program();
bool checkShaderCompilation(GLuint shaderID);
bool compile_and_attach_shader(GLuint programID, unsigned int type, const char* path);
GLuint load_texture(std::string path);

GLuint create_cube() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	return vao;

}

GLuint createQuadVao1() {

	GLfloat positions[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};

	GLfloat colours[] = {
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
	};

	GLfloat texCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint position_vbo;
	glGenBuffers(1, &position_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	GLuint colour_vbo;
	glGenBuffers(1, &colour_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colour_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);

	GLuint texture_vbo;
	glGenBuffers(1, &texture_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(2);

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	glBindVertexArray(0);

	return vao;
}

GLuint createTriangleVao() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLfloat vertices[] = {
		-0.8f, -0.8f, 1.0f,		1.0f, 0.0f, 0.0f, 1.0f,
		-0.8f,  0.8f, 1.0f,		0.0f, 1.0f, 0.0f, 1.0f,
		 0.0f, -0.4f, 1.0f,		0.0f, 0.0f, 1.0f, 1.0f,
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	return vao;
}

GLuint createFanVao1() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLfloat vertices[] = {
		 0.0f,  1.0f, 1.0f,		1.0f, 1.0f, 1.0f, 0.3f,
		-0.7f,  0.7f, 1.0f,		1.0f, 0.0f, 1.0f, 0.3f,
		-1.0f,  0.0f, 1.0f,		1.0f, 1.0f, 1.0f, 0.3f,
		-0.7f, -0.7f, 1.0f,		1.0f, 1.0f, 1.0f, 0.3f,
		 0.0f, -1.0f, 1.0f,		1.0f, 1.0f, 1.0f, 0.3f,
		 0.7f, -0.7f, 1.0f,		0.0f, 1.0f, 1.0f, 0.3f,
		 1.0f,  0.0f, 1.0f,		1.0f, 1.0f, 1.0f, 0.3f,
		 0.7f,  0.7f, 1.0f,		1.0f, 1.0f, 1.0f, 0.3f,
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	return vao;
}

int main(int argc, char** argv) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(600, 600, "OpenGL", NULL, NULL);

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

	glViewport(0, 0, 600, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glClearColor(0.5f, 0.25f, 0.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

	GLuint program = create_shader_program();

	GLuint quadVao1 = createQuadVao1();
	GLuint container_texture = load_texture("container.jpg");
	GLuint face_texture = load_texture("awesomeface.png");
	GLuint cube = create_cube();

	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, face_texture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, container_texture);

	GLuint texture_location_0 = glGetUniformLocation(program, "texture_slot0");
	GLuint texture_location_1 = glGetUniformLocation(program, "texture_slot1");
	glUniform1i(texture_location_0, 0); // set uniform to use slot 0 (face_texture)
	glUniform1i(texture_location_1, 1); // set uniform to use slot 1 (container_texture)

	GLuint opacityLocation = glGetUniformLocation(program, "opacity");
	glUniform1f(opacityLocation, 1.0f);

	GLuint mix_amount_location = glGetUniformLocation(program, "mix_amount");

	GLuint model_matrix = glGetUniformLocation(program, "model");

	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float mixAmount = sin(glfwGetTime()) / 2 + 0.5f;
		mixAmount = 1.0f;
		glUniform1f(mix_amount_location, mixAmount);

		glm::mat4 transform(1.0f);
		float rotationAmount = (float)sin(glfwGetTime()) * 60.0f;

		transform = glm::translate(transform, glm::vec3(0.5f, 0.5f, 0.0f));
		transform = glm::rotate(transform, glm::radians(rotationAmount), glm::vec3(0.0f, 1.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(0.25f, 0.25f, 0.25f));

		glUniformMatrix4fv(model_matrix, 1, GL_FALSE, glm::value_ptr(transform));

		glBindVertexArray(cube);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &quadVao1);
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

GLuint load_texture(std::string path) {
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, numChannels;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &numChannels, 4);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	return texture;
}
