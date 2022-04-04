#pragma once
#include <glm/glm.hpp>

class ShaderLight {
public:
	ShaderLight(
		glm::vec3 position,
		glm::vec3 ambient,
		glm::vec3 diffuse,
		glm::vec3 specular
	);

	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};
