#include<iostream>

int* generate_cube_vertices() {
	int numSides = 6;
	int numVerticesPerSide = 4;
	int vertexWidth = 8;
	int dataSize = numSides * numVerticesPerSide * vertexWidth;

	int* vertices = new int[dataSize];

	for (int i = 0; i < dataSize; i++)
		vertices[i] = 0;

	int positionOffset = 0;
	int normalOffset = 3;
	int textureOffset = 6;

	for (int i = 0; i < 6; i++) {

		int axis = i % 3;
		int sign = 1 - 2 * (i % 2);
		//	axis and sign will iterate through:
		//	0,  1,  2,  0,  1,  2
		//	1, -1,  1, -1,  1, -1
		std::cout << "axis=" << axis << ", sign=" << sign << std::endl;

		//	determine the other 2 coords to update in each position, 
		//	i.e. must skip the axis component,
		//	which is fixed for the current side

		int p1 = 0;
		while (p1 == axis) p1++;
		int p2 = p1 + 1;
		while (p2 == axis) p2++;

		//	determine where to start populating elements (each side = 12 elements)

		int start = i * numVerticesPerSide * vertexWidth;

		//	populate the first position of the side

		vertices[positionOffset + start + axis] = sign;
		vertices[positionOffset + start + p1] = -1;
		vertices[positionOffset + start + p2] = -1;

		//	populate first normal

		vertices[start + normalOffset + axis] = sign;

		for (int currentVertex = 1; currentVertex < 4; currentVertex++) {

			//	-------------------
			//	set position values
			//	-------------------
			
			vertices[positionOffset + start + currentVertex * vertexWidth + axis] = sign;

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

			vertices[normalIndex] = sign;

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

void print_vertices(int *vertices, int numSides, int numVerticesPerSide, int vertexWidth, std::ostream& dest) {
	for (int side = 0; side < numSides; side++) {
		for (int pos = 0; pos < numVerticesPerSide; pos++) {
			for (int comp = 0; comp < vertexWidth; comp++) {
				dest << vertices[side * (numVerticesPerSide * vertexWidth) + pos * vertexWidth + comp] << ", ";
			}
			dest << "\n";
		}
		dest << "\n";
	}
}

int main() {

	int* vertices = generate_cube_vertices();
	print_vertices(vertices, 6, 4, 8, std::cout);
	delete[] vertices;

	return 0;
}
