#include "mesh.h"

Mesh::Mesh() : vertices(nullptr), elements(nullptr) {}

Mesh::~Mesh() {
	if (vertices != nullptr) {
		delete[] vertices;
	}
	if (elements != nullptr) {
		delete[] elements;
	}
}

float* Mesh::getVertices() const {
	return vertices;
}

int* Mesh::getElements() const {
	return elements;
}

