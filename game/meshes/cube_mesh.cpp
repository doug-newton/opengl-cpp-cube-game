#include "cube_mesh.h"

CubeMesh::CubeMesh() {
	vertices = generateVertices();
	elements = generateElements();
}

float* CubeMesh::generateVertices() {
	int numSides = 6;
	int numVerticesPerSide = 4;
	int vertexWidth = 8;
	int dataSize = numSides * numVerticesPerSide * vertexWidth;

	float* vertices = new float[dataSize];

	for (int i = 0; i < dataSize; i++)
		vertices[i] = 0.0f;

	int positionOffset = 0;
	int normalOffset = 3;
	int textureOffset = 6;

	for (int sideIndex = 0; sideIndex < 6; sideIndex++) {
		generateSide(
			vertices,
			numVerticesPerSide,
			vertexWidth,
			positionOffset,
			normalOffset,
			textureOffset,
			sideIndex
		);
	}

	return vertices;
}

int* CubeMesh::generateElements() {
	int* result = new int[36];

	int order[] = { 0, 1, 2, 2, 3, 0 };

	for (int s = 0; s < 6; s++) {
		for (int o = 0; o < 6; o++) {
			result[s * 6 + o] = s * 4 + order[o];
		}
	}

	return result;
}

int CubeMesh::getElementDataSize() {
	return 36 * sizeof(int);
}

int CubeMesh::getVertexDataSize() {
	return 192 * sizeof(float);
}
