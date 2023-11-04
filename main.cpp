#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "textures.h"
#include "vaos.h"
#include "gl_util.h"
#include <vector>
#include "game/game.h"
#include <fstream>

int glMain();

class Mesh {

protected:

	int size;
	float* data;

public:

	Mesh(int size) : size(size), data(new float[size]) {

	}

	~Mesh() {
		delete[] data;
	}

	float get(int i) {
		return data[i];
	}

	int getSize() const {
		return size;
	}

};

enum {
LEFT = -1,
BOTTOM = -1,
FRONT = -1,
TOP = 1,
BACK = 1,
RIGHT = 1,
};

static int positions[][3] = {

	{ LEFT, BOTTOM, FRONT },
	{ LEFT, TOP, FRONT },
	{ LEFT, TOP, BACK },
	{ LEFT, BOTTOM, BACK },

	{ RIGHT, BOTTOM, FRONT },
	{ RIGHT, TOP, FRONT },
	{ RIGHT, TOP, BACK },
	{ RIGHT, BOTTOM, BACK },

};

int LBF[] = { LEFT, BOTTOM, FRONT };
int LTF[] = { LEFT, TOP, FRONT };
int LTB[] = { LEFT, TOP, BACK };
int LBB[] = { LEFT, BOTTOM, BACK };

int RBF[] = { RIGHT, BOTTOM, FRONT };
int RTF[] = { RIGHT, TOP, FRONT };
int RTB[] = { RIGHT, TOP, BACK };
int RBB[] = { RIGHT, BOTTOM, BACK };

int* leftSide[] = { LBF, LTF, LTB, LBB };
int* rightSide[] = { RBF, RTF, RTB, RBB };

int** sides[] = { leftSide, rightSide };

class Vertex {

};

class Side {
};

class Cube : public Mesh {

public:

	Cube() : Mesh(108) {
		left = bottom = front = -1;
		right = top = back = 1;

		for (int i = 0; i < 108; i++)	
			data[i] = 0.0f;

		makeXSide(left, 0);
		makeXSide(right, 18);
	}

	void makeXSide(int side, int start) {
		makeXTriangle1(side, start);
		makeXTriangle2(side, start);

		float points[] = {
			side, front, bottom,
			side, front, top,
			side, back, top,
			side, back, bottom,
		};

		int indices[] = { 0, 1, 2, 2, 3, 0 };
	}

	void makeXTriangle1(int side, int startOfSide) {
		float points[] = {
			side, front, bottom,
			side, front, top,
			side, back, top
		};

		for (int p = 0; p < 9; p++) {
			data[startOfSide + p] = points[p];
		}
	}

	void makeXTriangle2(int side, int startOfSide) {
		float points[] = {
			side, back, top,
			side, back, bottom,
			side, front, bottom
		};

		for (int p = 0; p < 9; p++) {
			data[startOfSide + p + 9] = points[p];
		}
	}

	void print(std::ostream& output) {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				for (int k = 0; k < 3; k++) {
					int p = i * 18 + j * 3 + k;
					output << data[p] << ", ";
				}
				output << "\n";
			}
			output << "\n";
		}
	}

private:

		int left, bottom, front;
		int right, top, back;

};

int main() {
	Cube cube;

	cube.print(std::cout);

	return 0;
}

int glMain()
{
	Game game;

	if (!game.init())
		return -1;

	game.mainLoop();

	glfwTerminate();

	return 0;
}
