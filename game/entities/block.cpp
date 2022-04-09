#include "block.h"

Block::Block() 
	:
	vao(0),
	material(
		glm::vec3(1.0f, 0.5f, 0.31f),
		glm::vec3(1.0f, 0.5f, 0.31f),
		glm::vec3(0.5f, 0.5f, 0.9f),
		32.0f),
	position(0.0f, 0.0f, -3.0f)
{
}

bool Block::init() {
	vao = createCubeWithNormals();
	return true;
}

void Block::render() {
	Renderer::instance().getLightingShader()->use();

	Renderer::instance().getLightingShader()->setMaterial(material);
	glBindVertexArray(vao);
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, position);
	transform = glm::scale(transform, glm::vec3(3.0f, 3.0f, 3.0f));
	Renderer::instance().getLightingShader()->setModel(transform);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}