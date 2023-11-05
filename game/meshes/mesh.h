#pragma once

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
};

