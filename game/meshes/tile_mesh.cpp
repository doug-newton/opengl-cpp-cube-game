#include "tile_mesh.h"

TileMesh::TileMesh() {
	vertices = generateVertices();
	elements = generateElements();
}

float* TileMesh::generateVertices() {
	int numSides = 1;
	int numVerticesPerSide = 4;
	int vertexWidth = 8;
	int dataSize = numSides * numVerticesPerSide * vertexWidth;

	float* vertices = new float[dataSize];

	for (int i = 0; i < dataSize; i++)
		vertices[i] = 0.0f;

	int positionOffset = 0;
	int normalOffset = 3;
	int textureOffset = 6;

	generateSide(
		vertices,
		numVerticesPerSide,
		vertexWidth,
		positionOffset,
		normalOffset,
		textureOffset,
		//	4 = the top side of a cube
		4,
		//	only one side - so start of population not determined by side index
		true
	);

	return vertices;
}

int* TileMesh::generateElements() {
	int* result = new int[6];

	int order[] = { 0, 1, 2, 2, 3, 0 };

	for (int s = 0; s < 1; s++) {
		for (int o = 0; o < 6; o++) {
			result[s * 6 + o] = s * 4 + order[o];
		}
	}

	return result;
}

int TileMesh::getElementDataSize() {
	return 6 * sizeof(int);
}

int TileMesh::getVertexDataSize() {
	return 32 * sizeof(float);
}
