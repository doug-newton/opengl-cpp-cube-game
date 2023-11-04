#pragma once

class Side {

	int numVertices;
	int vertexSize;
	float *vertexData;

	int numElements;
	int* elementData;

public:

	Side(int numVertices, int vertexSize, int numElements);
	void fillVertexData(int index, int count, float* data);

};

Side::Side(int numVertices, int vertexSize, int numElements)
	: 
	numVertices(numVertices),
	vertexSize(vertexSize),
	vertexData(new float[numVertices * vertexSize]),
	numElements(numElements),
	elementData(new int[numElements])
{
}

void Side::fillVertexData(int index, int count, float* data)
{
	for (int i = 0; i < numElements; i++) {
		vertexData[index + i] = data[i];
	}
}

void DoSomething() {

}
