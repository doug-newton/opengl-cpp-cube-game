#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "entity.h"
#include "../renderer.h"
#include "../meshes/vaos.h"
#include "../shaders/lighting/shader_material.h"

class Block : public Entity {

private:

	std::shared_ptr<VaoReference> vao;

	ShaderMaterial material;

	glm::vec3 position;

	int type;
public:

	Block(int type, float x, float y, float z);

	bool init();
	void render();

};
