#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "../shader_compiler.h"

class SimpleShader {

private:
	const static std::string vertexSource;
	const static std::string fragmentSource;

public:

	SimpleShader();

	void use();

	void setModel(const glm::mat4& model);

	void setView(const glm::mat4& view);

	void setProjection(const glm::mat4& projection);

	void setObjectColor(const glm::vec3& objectColor);

private:
	GLuint id;

	int modelLocation;
	int viewLocation;
	int projectionLocation;
	int objectColorLocation;
};
