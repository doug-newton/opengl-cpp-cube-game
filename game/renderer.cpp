#include "renderer.h"

Renderer::Renderer() 
	:
	simpleShader(nullptr),
	lightingShader(nullptr)
{
	simpleShader = new SimpleShader();
	lightingShader = new LightingShader();
}

Renderer::~Renderer() {
	delete simpleShader;
	delete lightingShader;
}

SimpleShader* Renderer::getSimpleShader() {
	return simpleShader;
}

LightingShader* Renderer::getLightingShader() {
	return lightingShader;
}