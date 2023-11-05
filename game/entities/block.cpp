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
	type(type)
{
}

bool Block::init() {
vao = createCubeUsingCubeMesh();
	//	vao = createPlaneWithNormalsAndTexCoords();
	return true;
}

void Block::render() {
	Renderer::instance().getLightingShader()->use();
	Renderer::instance().getLightingShader()->setMaterial(material);
	Renderer::instance().getLightingShader()->setTileIndex(type);
	glBindVertexArray(vao);
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, position);
	Renderer::instance().getLightingShader()->setModel(transform);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}