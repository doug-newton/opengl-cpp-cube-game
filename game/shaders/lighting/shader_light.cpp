#include "shader_light.h"

ShaderLight::ShaderLight(
	glm::vec3 position,
	glm::vec3 ambient,
	glm::vec3 diffuse,
	glm::vec3 specular
)
	:
	position(position),
	ambient(ambient),
	diffuse(diffuse),
	specular(specular)
{ }