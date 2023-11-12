#include "tile_shader.h"

TileShader::TileShader() 
	:
	tileset(0)
{
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

	rotationOnlyLocation = glGetUniformLocation(this->id, "rotation");
	modelLocation = glGetUniformLocation(this->id, "model");
	viewLocation = glGetUniformLocation(this->id, "view");
	projectionLocation = glGetUniformLocation(this->id, "projection");
	viewPosLocation = glGetUniformLocation(this->id, "viewPos");

	tilesetLocation = glGetUniformLocation(this->id, "tileset");
	tileIndexLocation = glGetUniformLocation(this->id, "tileIndex");

	tileset = loadPng("tileset.png");
	setTileset(tileset);
	setTileIndex(0);
}

TileShader::~TileShader() {
	glDeleteProgram(id);
}

void TileShader::use() {
	glUseProgram(this->id);
}

void TileShader::setMaterial(const ShaderMaterial& material) {
	glUniform3fv(materialAmbientLocation, 1, glm::value_ptr(material.ambient));
	glUniform3fv(materialDiffuseLocation, 1, glm::value_ptr(material.diffuse));
	glUniform3fv(materialSpecularLocation, 1, glm::value_ptr(material.specular));
	glUniform1f(materialShininessLocation, material.shininess);
}

void TileShader::setLight(const ShaderLight& light) {
	glUniform3fv(lightPositionLocation, 1, glm::value_ptr(light.position));
	glUniform3fv(lightAmbientLocation, 1, glm::value_ptr(light.ambient));
	glUniform3fv(lightDiffuseLocation, 1, glm::value_ptr(light.diffuse));
	glUniform3fv(lightSpecularLocation, 1, glm::value_ptr(light.specular));
}

void TileShader::setModel(const glm::mat4& model) {
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
}

void TileShader::setRotationOnly(const glm::mat4& rotationOnly) {
	glUniformMatrix4fv(rotationOnlyLocation, 1, GL_FALSE, glm::value_ptr(rotationOnly));
}

void TileShader::setView(const glm::mat4& view) {
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
}

void TileShader::setProjection(const glm::mat4& projection) {
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
}

void TileShader::setViewPos(const glm::vec3& viewPos) {
	glUniform3fv(viewPosLocation, 1, glm::value_ptr(viewPos));
}

void TileShader::setTileset(GLuint texture) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1ui(tilesetLocation, 0);
}

void TileShader::setTileIndex(int index) {
	glUniform1i(tileIndexLocation, index);
}

void TileShader::setCamera(Camera* camera) {
	setProjection(camera->getProjectionMatrix());
	setView(camera->getViewMatrix());
	setViewPos(camera->getPosition());
}
