#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "entity.h"
#include "../renderer.h"
#include "../shaders/lighting/shader_light.h"
#include "../renderer.h"
#include "../../vaos.h"

class Light : public Entity {
private:
	GLuint vao;
	ShaderLight shaderLight;
public:
	Light(float x, float y, float z);
	bool init();
	void render();
	const ShaderLight& getShaderLight();
};