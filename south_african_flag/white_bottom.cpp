#include "south_african_flag.h"

GLuint white_bottom() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLfloat vertices[] = {
		0.01f, -0.1f, 1.0f,		1.0f, 1.0f, 1.0f, 1.0f, 
		0.5f,  -0.1f, 1.0f,		1.0f, 1.0f, 1.0f, 1.0f, 
		0.5f,  -0.5f, 1.0f,		1.0f, 1.0f, 1.0f, 1.0f, 
		-0.4f, -0.5f, 1.0f,		1.0f, 1.0f, 1.0f, 1.0f, 
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	GLint elements[] = {
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