#include "simple_shader.h"

SimpleShader::SimpleShader() {
	this->id = ShaderCompiler::compileShaderProgram(
		vertexSource.c_str(),
		fragmentSource.c_str()
	);

	modelLocation = glGetUniformLocation(this->id, "model");
	viewLocation = glGetUniformLocation(this->id, "view");
	projectionLocation = glGetUniformLocation(this->id, "projection");
	objectColorLocation = glGetUniformLocation(this->id, "objectColor");
}

void SimpleShader::use() {
	glUseProgram(this->id);
}

void SimpleShader::setModel(const glm::mat4& model) {
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
}

void SimpleShader::setView(const glm::mat4& view) {
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
}

void SimpleShader::setProjection(const glm::mat4& projection) {
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
}

void SimpleShader::setObjectColor(const glm::vec3& objectColor) {
	glUniform3fv(objectColorLocation, 1, glm::value_ptr(objectColor));
}
