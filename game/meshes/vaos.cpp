#include "vaos.h"
#include "mesh.h"
#include "cube_mesh.h"
#include "tile_mesh.h"

GLuint createVao(Mesh* mesh);

GLuint createCubeUsingCubeMesh() {
	static GLuint vao = 0;

	if (vao != 0) {
		return vao;
	}

	CubeMesh mesh;

	return createVao(&mesh);
}

GLuint createTileVao() {
	static GLuint vao = 0;

	if (vao != 0) {
		return vao;
	}

	TileMesh mesh;

	return createVao(&mesh);
}

GLuint createVao(Mesh* mesh) {
	GLuint vao = 0;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, 
		mesh->getVertexDataSize(),
		mesh->getVertices(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getElementDataSize(), mesh->getElements(), GL_STATIC_DRAW);

	glBindVertexArray(0);

	return vao;
}
