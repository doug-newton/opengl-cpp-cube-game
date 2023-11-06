#include "vao_reference.h"

VaoReference::VaoReference(GLuint vao, GLuint vbo, GLuint ebo, int eboLength) 
	: vao(vao), vbo(vbo), ebo(ebo), eboLength(eboLength)
{
}

VaoReference::~VaoReference() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

GLuint VaoReference::getVao() const {
	return vao;
}

int VaoReference::getEboLength() const {
	return eboLength;
}