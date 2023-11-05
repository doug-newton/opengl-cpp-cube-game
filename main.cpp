#include <iostream>
#include <fstream>
#include "game/meshes/cube_mesh.h"

void print_vertices(float *vertices, int numSides, int numVerticesPerSide, int vertexWidth, std::ostream& dest) {
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

void print_elements(int* elements, std::ostream& out) {
	for (int s = 0; s < 6; s++) {
		for (int o = 0; o < 6; o++) {
			out << elements[s * 6 + o] << ", ";
		}
		out << "\n";
	}
}

int main() {
	CubeMesh mesh;

	std::ofstream outfile("vertices.txt");
	print_vertices(mesh.getVertices(), 6, 4, 8, outfile);
	outfile.close();

	print_elements(mesh.getElements(), std::cout);

	return 0;
}
