#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "shader_material.h"
#include "shader_light.h"
#include "../shader_compiler.h"

class LightingShader {

	const static std::string vertexSource;
	const static std::string fragmentSource;

public:

	LightingShader();

	void use();

	void setMaterial(const ShaderMaterial& material);

	void setLight(const ShaderLight& light);

	void setModel(const glm::mat4& model);

	void setView(const glm::mat4& view);

	void setProjection(const glm::mat4& projection);

	void setViewPos(const glm::vec3& viewPos);

private:
	GLuint id;

	int materialAmbientLocation;
	int materialDiffuseLocation;
	int materialSpecularLocation;
	int materialShininessLocation;

	int lightPositionLocation;
	int lightAmbientLocation;
	int lightDiffuseLocation;
	int lightSpecularLocation;

	int modelLocation;
	int viewLocation;
	int projectionLocation;
	int viewPosLocation;
};
