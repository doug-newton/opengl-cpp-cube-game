#pragma once

void generateSide(
	float* vertices,
	int numVerticesPerSide,
	int vertexWidth,
	int positionOffset,
	int normalOffset,
	int textureOffset,
	int sideIndex);

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
	int p2);
