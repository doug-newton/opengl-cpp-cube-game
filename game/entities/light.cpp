#include "light.h"

Light::Light()
	:
	vao(0),
	shaderLight(
		glm::vec3(-3.0f, 5.0f, -3.0f),
		glm::vec3(0.2f, 0.2f, 0.2f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 1.0f, 1.0f)
	)
{
}

bool Light::init() {
	vao = createLightVao();
	return true;
}

void Light::render() {
	Renderer::instance().getLightingShader()->use();

	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, shaderLight.position);
	lightModel = glm::scale(lightModel, glm::vec3(0.2f));

	Renderer::instance().getSimpleShader()->use();
	Renderer::instance().getSimpleShader()->setObjectColor(shaderLight.ambient);

	glBindVertexArray(vao);
	Renderer::instance().getSimpleShader()->setModel(lightModel);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

const ShaderLight& Light::getShaderLight() {
	return shaderLight;
}
