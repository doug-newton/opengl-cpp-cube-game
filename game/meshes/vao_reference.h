#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VaoReference {
private:
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	int eboLength;

public:
	VaoReference(GLuint vao, GLuint vbo, GLuint ebo, int eboLength);
	~VaoReference();

	GLuint getVao() const;
	int getEboLength() const;
};
