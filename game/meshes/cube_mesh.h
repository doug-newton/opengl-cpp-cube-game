#pragma once

#include "mesh.h"

class CubeMesh: public Mesh {
protected:
	virtual float* generateVertices() override;
	virtual int* generateElements() override;
public:
	CubeMesh();
	virtual int getVertexDataSize() override;
	virtual int getElementDataSize() override;
};

