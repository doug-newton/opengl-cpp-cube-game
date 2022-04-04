#pragma once
#include <glm/glm.hpp>

class ShaderMaterial {
public:
	ShaderMaterial(
		glm::vec3 ambient,
		glm::vec3 diffuse,
		glm::vec3 specular,
		float shininess
	);

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};
