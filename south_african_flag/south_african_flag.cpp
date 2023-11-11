#include "south_african_flag.h"

GLuint south_african_flag() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLfloat vertices[] = {
		//	green background
		-0.5f, -0.5f, 1.0f,		0.0f, 0.6f, 0.0f, 1.0f,
		 0.5f, -0.5f, 1.0f,		0.0f, 0.6f, 0.0f, 1.0f,
		 0.5f,  0.5f, 1.0f,		0.0f, 0.6f, 0.0f, 1.0f,
		-0.5f,  0.5f, 1.0f,		0.0f, 0.6f, 0.0f, 1.0f,
		//	white top
		0.01f, 0.1f, 1.0f,		1.0f, 1.0f, 1.0f, 1.0f, 
		0.5f, 0.1f, 1.0f,		1.0f, 1.0f, 1.0f, 1.0f, 
		0.5f, 0.5f, 1.0f,		1.0f, 1.0f, 1.0f, 1.0f, 
		-0.4f, 0.5f, 1.0f,		1.0f, 1.0f, 1.0f, 1.0f, 
		//	white bottom
		0.01f, -0.1f, 1.0f,		1.0f, 1.0f, 1.0f, 1.0f, 
		0.5f,  -0.1f, 1.0f,		1.0f, 1.0f, 1.0f, 1.0f, 
		0.5f,  -0.5f, 1.0f,		1.0f, 1.0f, 1.0f, 1.0f, 
		-0.4f, -0.5f, 1.0f,		1.0f, 1.0f, 1.0f, 1.0f, 
		//	red top
		0.030f, 0.12f, 1.0f,		1.0f, 0.0f, 0.0f, 1.0f, 
		0.5f, 0.12f, 1.0f,		1.0f, 0.0f, 0.0f, 1.0f, 
		0.5f, 0.5f, 1.0f,		1.0f, 0.0f, 0.0f, 1.0f, 
		-0.37f, 0.5f, 1.0f,		1.0f, 0.0f, 0.0f, 1.0f, 
		//	blue bottom
		0.030f, -0.12f, 1.0f,		0.0f, 0.0f, 1.0f, 1.0f, 
		0.5f,   -0.12f, 1.0f,		0.0f, 0.0f, 1.0f, 1.0f, 
		0.5f,   -0.5f, 1.0f,		0.0f, 0.0f, 1.0f, 1.0f, 
		-0.37f, -0.5f, 1.0f,		0.0f, 0.0f, 1.0f, 1.0f, 
		//	golden triangle
		-0.5f, -0.3f,  1.0f,		0.8f, 0.7f, 0.0f, 1.0f,
		-0.15f, 0.0f,  1.0f,		0.8f, 0.7f, 0.0f, 1.0f,
		-0.5f,  0.3f,  1.0f,		0.8f, 0.7f, 0.0f, 1.0f,
		//	black triangle
		-0.5f,	-0.25f, 1.0f,		0.0f, 0.0f, 0.0f, 1.0f,
		-0.2f,  0.0,	1.0f,		0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,   0.25f, 1.0f,		0.0f, 0.0f, 0.0f, 1.0f,
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	GLuint elements[] = {
		//	green background
		0, 1, 2,
		2, 3, 0,
		//	white top
		4, 5, 6,
		6, 7, 4,
		//	white bottom
		8, 9, 10,
		10, 11, 8,
		//	red top
		12, 13, 14,
		14, 15, 12,
		//	blue bottom
		16, 17, 18,
		18, 19, 16,
		//	golden triangle
		20, 21, 22,
		//	black triangle
		23, 24, 25
	};

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	glBindVertexArray(0);

	return vao;
}