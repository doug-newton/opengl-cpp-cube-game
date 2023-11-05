#include "mesh_algorithm.h"

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

	//	populate first tex coords

	vertices[start + textureOffset + 0] = 0.0f;
	vertices[start + textureOffset + 1] = 0.0f;
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
	int sideIndex,
	bool oneSideOnly) {

	int axis = sideIndex % 3;
	int sign = 1 - 2 * (sideIndex % 2);

	int p1 = 0;
	while (p1 == axis) p1++;
	int p2 = p1 + 1;
	while (p2 == axis) p2++;

	//	determine where to start populating elements

	int start = oneSideOnly ? 0 : sideIndex * numVerticesPerSide * vertexWidth;

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
