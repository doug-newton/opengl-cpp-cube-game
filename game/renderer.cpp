#include "renderer.h"

Renderer::Renderer() 
	:
	simpleShader(nullptr),
	lightingShader(nullptr)
{
	simpleShader = new SimpleShader();
	lightingShader = new TileShader();
}

Renderer::~Renderer() {
	delete simpleShader;
	delete lightingShader;
}

SimpleShader* Renderer::getSimpleShader() {
	return simpleShader;
}

TileShader* Renderer::getTileShader() {
	return lightingShader;
}