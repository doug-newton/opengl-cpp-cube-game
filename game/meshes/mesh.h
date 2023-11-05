#pragma once

//	including for base classes of mesh to have access
#include "mesh_algorithm.h"

class Mesh {
protected:
	float* vertices;
	int* elements;
protected:
	virtual float* generateVertices() = 0;
	virtual int* generateElements() = 0;
public:
	Mesh();
	virtual ~Mesh();
	float* getVertices() const;
	int* getElements() const;
	virtual int getVertexDataSize() = 0;
	virtual int getElementDataSize() = 0;
};

