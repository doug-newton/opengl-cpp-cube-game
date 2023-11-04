#include<iostream>

void iterate_sides() {
	for (int i = 0; i < 6; i++) {
		int axis = i % 3;
		int sign = 1 - 2 * (i % 2);
		//	0,  1,  2,  0,  1,  2
		//	1, -1,  1, -1,  1, -1
		std::cout << "axis=" << axis << " " << sign << std::endl;

		int p = 0;
		while (p == axis) {
			p++;
		}
		std::cout << "altering " << p << std::endl;
		int p2 = p + 1;
		while (p2 == axis) {
			p2++;
		}
		std::cout << "altering " << p2 << std::endl;
		std::cout << std::endl;
	}
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

	iterate_sides();

	return 0;
}
