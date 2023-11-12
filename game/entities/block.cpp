#include "block.h"

Block::Block(int type, float x, float y, float z) 
	:
	vao(0),
	material(
		glm::vec3(0.9f, 0.9f, 0.9f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0.5f, 0.5f, 0.9f),
		32.0f),
	position(x, y, z),
	type(type),
	rotationAmount(0.0f)
{
}

bool Block::init() {
	vao = createCubeVao();
	return true;
}

void Block::update(float deltaTime) {
	rotationAmount += deltaTime * 100;
	if (rotationAmount > 360.0f) {
		rotationAmount -= 360.0f;
	}
}

void Block::render() {
	Renderer::instance().getTileShader()->use();
	Renderer::instance().getTileShader()->setMaterial(material);
	Renderer::instance().getTileShader()->setTileIndex(type);

	glBindVertexArray(vao.get()->getVao());

	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, position);
	transform = glm::rotate(transform, glm::radians(rotationAmount), glm::vec3(1.0f, 0.0f, 1.0f));

	Renderer::instance().getTileShader()->setModel(transform);

	glm::mat4 rotation_only = glm::mat4(1.0f);
	rotation_only = glm::rotate(rotation_only, glm::radians(rotationAmount), glm::vec3(1.0f, 0.0f, 1.0f));

	Renderer::instance().getTileShader()->setRotationOnly(rotation_only);

	glDrawElements(GL_TRIANGLES, vao.get()->getEboLength(), GL_UNSIGNED_INT, nullptr);
}