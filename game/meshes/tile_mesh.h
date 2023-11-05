#pragma once

#include "mesh.h"

class TileMesh : public Mesh {
protected:
	virtual float* generateVertices() override;
	virtual int* generateElements() override;
public:
	TileMesh();
	virtual int getVertexDataSize() override;
	virtual int getElementDataSize() override;
};
