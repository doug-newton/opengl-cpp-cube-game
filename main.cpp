#include<iostream>

void generate_cube_vertices() {
	int numSides = 6;
	int numVerticesPerSide = 4;
	int numElementsPerVertex = 3;
	int dataSize = numSides * numVerticesPerSide * numElementsPerVertex;

	int* vertices = new int[dataSize];

	for (int i = 0; i < dataSize; i++)
		vertices[i] = 0;

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

		int start = i * 12;

		//	populate the first position of the side

		vertices[start + axis] = sign;
		vertices[start + p1] = -1;
		vertices[start + p2] = -1;

		for (int c = 1; c < 4; c++) {
			vertices[start + c * 3 + axis] = sign;

			// by default, set the current other 2 coords to the previous

			vertices[start + c * 3 + p1] = vertices[start + (c - 1) * 3 + p1];
			vertices[start + c * 3 + p2] = vertices[start + (c - 1) * 3 + p2];

			//	then take turns on which coord to flip
			//	first flip p1, then flip p2, then flip p1

			if (c % 2 == 1) {
				vertices[start + c * 3 + p1] = -vertices[start + c * 3 + p1];
			}
			else {
				vertices[start + c * 3 + p2] = -vertices[start + c * 3 + p2];
			}
		}
	}

	for (int side = 0; side < numSides; side++) {
		for (int pos = 0; pos < numVerticesPerSide; pos++) {
			for (int comp = 0; comp < numElementsPerVertex; comp++) {
				std::cout << vertices[side * (numVerticesPerSide * numElementsPerVertex) + pos * numElementsPerVertex + comp] << ", ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	delete[] vertices;
}

void iterate_corners() {

	int x = -1;
	int y = -1;

	int positions[8] = {
		-1, -1,
		 0,  0,
		 0,  0,
		 0,  0,
	};

	std::cout << x << " " << y << std::endl;

	for (int i = 0; i < 3; i++) {
		if (i % 2 == 0) {
			x = -x;
		}
		else {
			y = -y;
		}
		std::cout << x << " " << y << std::endl;
	}
}

int main() {

	generate_cube_vertices();

	return 0;
}
