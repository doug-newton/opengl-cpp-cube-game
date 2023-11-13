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

	return 0;
}
