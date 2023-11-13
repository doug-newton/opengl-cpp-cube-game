#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void print(std::string label, glm::mat4& matrix) {
	std::cout << label << ":" << std::endl;

	float* p = glm::value_ptr(matrix);

	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			int offset = c * 4 + r;
			std::cout << *(p + offset) << " ";
		}
		std::cout << std::endl;
	}
}

void print(std::string label, glm::vec4& vec) {
	std::cout << label << ":" << std::endl;
	float* p = glm::value_ptr(vec);

	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 1; c++) {
			int offset = c * 4 + r;
			std::cout << *(p + offset) << " ";
		}
		std::cout << std::endl;
	}
}

int main(int argc, char** argv) {
	glm::mat4 matrix(1.0f);
	print("identity", matrix);

	//	x -> x + 1
	//	y -> y + 2
	//	T
	matrix = glm::translate(matrix, glm::vec3(1.0f, 2.0f, 0.0f));
	print("translate", matrix);

	//	x -> 2x + 1
	//	y -> 2y + 2
	//	T x S (translation happens after scaling)
	//	apply transformations from right to left
	matrix = glm::scale(matrix, glm::vec3(2.0f, 2.0f, 1.0f));
	print("scale", matrix);

	glm::vec4 pos(1.0f, 1.0f, 1.0f, 1.0f);
	print("start", pos);

	//	T x [S x p]
	glm::vec4 result = matrix * pos;
	print("result", result);

	return 0;
}
