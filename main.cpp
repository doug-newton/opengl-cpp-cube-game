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

int main(int argc, char** argv) {
	glm::mat4 matrix(1.0f);
	print("identity", matrix);

	//	x -> x + 1
	//	y -> y + 2
	matrix = glm::translate(matrix, glm::vec3(1.0f, 2.0f, 0.0f));
	print("translate", matrix);

	//	x -> 2x + 1
	//	y -> 2y + 2
	matrix = glm::scale(matrix, glm::vec3(2.0f, 2.0f, 1.0f));
	print("scale", matrix);

	return 0;
}
