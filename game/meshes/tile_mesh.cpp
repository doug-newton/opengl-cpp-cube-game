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

	for (int i = 4; i < 5; i++) {

		//	axis and sign will iterate through:
		//	0,  1,  2,  0,  1,  2
		//	1, -1,  1, -1,  1, -1

		int axis = i % 3;
		int sign = 1 - 2 * (i % 2);

		//	determine the other 2 coords to update in each position, 
		//	i.e. must skip the axis component,
		//	which is fixed for the current side

		int p1 = 0;
		while (p1 == axis) p1++;
		int p2 = p1 + 1;
		while (p2 == axis) p2++;

		//	determine where to start populating elements (each side = 12 elements)

		int start = 0;

		//	populate the first position of the side

		vertices[positionOffset + start + axis] = (float)sign * 0.5f;
		vertices[positionOffset + start + p1] = -1 * 0.5f;
		vertices[positionOffset + start + p2] = -1 * 0.5f;

		//	populate first normal

		vertices[start + normalOffset + axis] = (float)sign * 1.0f;

		for (int currentVertex = 1; currentVertex < 4; currentVertex++) {

			//	-------------------
			//	set position values
			//	-------------------

			vertices[positionOffset + start + currentVertex * vertexWidth + axis] = sign * 0.5f;

			// by default, set the current other 2 coords to the previous

			int p1CurrentIndex = positionOffset + start + currentVertex * vertexWidth + p1;
			int p1LastIndex = positionOffset + start + (currentVertex - 1) * vertexWidth + p1;

			int p2CurrentIndex = positionOffset + start + currentVertex * vertexWidth + p2;
			int p2LastIndex = positionOffset + start + (currentVertex - 1) * vertexWidth + p2;

			//	then take turns on which coord to flip
			//	first flip p1, then flip p2, then flip p1

			if (currentVertex % 2 == 1) {
				vertices[p1CurrentIndex] = -vertices[p1LastIndex];
				vertices[p2CurrentIndex] = vertices[p2LastIndex];
			}
			else {
				vertices[p1CurrentIndex] = vertices[p1LastIndex];
				vertices[p2CurrentIndex] = -vertices[p2LastIndex];
			}

			//	-----------------
			//	set normal values
			//	-----------------

			int normalIndex = start + currentVertex * vertexWidth + normalOffset + axis;

			vertices[normalIndex] = (float)sign * 1.0f;

			//	------------------
			//	set texture values
			//	------------------

			int t1CurrentIndex = start + currentVertex * vertexWidth + textureOffset + 0;
			int t2CurrentIndex = start + currentVertex * vertexWidth + textureOffset + 1;
			int t1LastIndex = start + (currentVertex - 1) * vertexWidth + textureOffset + 0;
			int t2LastIndex = start + (currentVertex - 1) * vertexWidth + textureOffset + 1;

			if (currentVertex % 2 == 1) {
				vertices[t1CurrentIndex] = 1 - vertices[t1LastIndex];
				vertices[t2CurrentIndex] = vertices[t2LastIndex];
			}
			else {
				vertices[t1CurrentIndex] = vertices[t1LastIndex];
				vertices[t2CurrentIndex] = 1 - vertices[t2LastIndex];
			}
		}
	}

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