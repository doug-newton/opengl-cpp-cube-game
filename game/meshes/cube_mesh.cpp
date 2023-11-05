#include "cube_mesh.h"

CubeMesh::CubeMesh() {
	vertices = generateVertices();
	elements = generateElements();
}

void setNormal(
	float* vertices,
	int vertexWidth,
	int start,
	int axis,
	int sign,
	int normalOffset,
	int currentVertex
) {
	int normalIndex = start + currentVertex * vertexWidth + normalOffset + axis;
	vertices[normalIndex] = (float)sign * 1.0f;
}

void setFirstVertex(
	float* vertices,
	int start,
	int axis,
	int sign,
	int positionOffset,
	int normalOffset,
	int textureOffset,
	int p1,
	int p2) {
	//	populate the first position of the side

	vertices[positionOffset + start + axis] = (float)sign * 0.5f;
	vertices[positionOffset + start + p1] = -1 * 0.5f;
	vertices[positionOffset + start + p2] = -1 * 0.5f;

	//	populate first normal

	vertices[start + normalOffset + axis] = (float)sign * 1.0f;

}

void setPositionValues(
	float* vertices,
	int start,
	int axis,
	int sign,
	int positionOffset,
	int vertexWidth,
	int p1,
	int p2,
	int currentVertex) {
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
}

void setTextureValues(float * vertices, int start, int vertexWidth, int textureOffset, int currentVertex) {
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

void generateCorners(
	float* vertices,
	int vertexWidth,
	int start,
	int axis,
	int sign,
	int positionOffset,
	int normalOffset,
	int textureOffset,
	int p1,
	int p2) {
	for (int currentVertex = 0; currentVertex < 4; currentVertex++) {

		if (currentVertex == 0) {
			setFirstVertex(
				vertices,
				start,
				axis,
				sign,
				positionOffset,
				normalOffset,
				textureOffset,
				p1,
				p2
			);
			continue;
		}

		//	-------------------
		//	set position values
		//	-------------------

		setPositionValues(
			vertices,
			start,
			axis,
			sign,
			positionOffset,
			vertexWidth,
			p1,
			p2,
			currentVertex);

		//	-----------------
		//	set normal values
		//	-----------------

		setNormal(
			vertices,
			vertexWidth,
			start,
			axis,
			sign,
			normalOffset,
			currentVertex
		);

		//	------------------
		//	set texture values
		//	------------------

		setTextureValues(
			vertices,
			start,
			vertexWidth,
			textureOffset,
			currentVertex
		);
	}
}

void generateSide(
	float* vertices, 
	int numVerticesPerSide,
	int vertexWidth,
	int positionOffset, 
	int normalOffset,
	int textureOffset,
	int i) {

	int axis = i % 3;
	int sign = 1 - 2 * (i % 2);

	int p1 = 0;
	while (p1 == axis) p1++;
	int p2 = p1 + 1;
	while (p2 == axis) p2++;

	//	determine where to start populating elements

	int start = i * numVerticesPerSide * vertexWidth;

	generateCorners(
		vertices,
		vertexWidth,
		start,
		axis,
		sign,
		positionOffset,
		normalOffset,
		textureOffset,
		p1,
		p2
	);
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

	for (int i = 0; i < 6; i++) {
		generateSide(
			vertices,
			numVerticesPerSide,
			vertexWidth,
			positionOffset,
			normalOffset,
			textureOffset,
			i
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
