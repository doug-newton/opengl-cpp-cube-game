#include "lighting_shader.h"

LightingShader::LightingShader() {
	this->id = ShaderCompiler::compileShaderProgram(
		vertexSource.c_str(),
		fragmentSource.c_str()
	);

	materialAmbientLocation = glGetUniformLocation(this->id, "material.ambient");
	materialDiffuseLocation = glGetUniformLocation(this->id, "material.diffuse");
	materialSpecularLocation = glGetUniformLocation(this->id, "material.specular");
	materialShininessLocation = glGetUniformLocation(this->id, "material.shininess");

	lightPositionLocation = glGetUniformLocation(this->id, "light.position");
	lightAmbientLocation = glGetUniformLocation(this->id, "light.ambient");
	lightDiffuseLocation = glGetUniformLocation(this->id, "light.diffuse");
	lightSpecularLocation = glGetUniformLocation(this->id, "light.specular");

	modelLocation = glGetUniformLocation(this->id, "model");
	viewLocation = glGetUniformLocation(this->id, "view");
	projectionLocation = glGetUniformLocation(this->id, "projection");
	viewPosLocation = glGetUniformLocation(this->id, "viewPos");
}


void LightingShader::use() {
	glUseProgram(this->id);
}

void LightingShader::setMaterial(const ShaderMaterial& material) {
	glUniform3fv(materialAmbientLocation, 1, glm::value_ptr(material.ambient));
	glUniform3fv(materialDiffuseLocation, 1, glm::value_ptr(material.diffuse));
	glUniform3fv(materialSpecularLocation, 1, glm::value_ptr(material.specular));
	glUniform1f(materialShininessLocation, material.shininess);
}

void LightingShader::setLight(const ShaderLight& light) {
	glUniform3fv(lightPositionLocation, 1, glm::value_ptr(light.position));
	glUniform3fv(lightAmbientLocation, 1, glm::value_ptr(light.ambient));
	glUniform3fv(lightDiffuseLocation, 1, glm::value_ptr(light.diffuse));
	glUniform3fv(lightSpecularLocation, 1, glm::value_ptr(light.specular));
}

void LightingShader::setModel(const glm::mat4& model) {
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
}

void LightingShader::setView(const glm::mat4& view) {
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
}

void LightingShader::setProjection(const glm::mat4& projection) {
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
}

void LightingShader::setViewPos(const glm::vec3& viewPos) {
	glUniform3fv(viewPosLocation, 1, glm::value_ptr(viewPos));
}

