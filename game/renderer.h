#pragma once

#include "shaders/simple/simple_shader.h"
#include "shaders/lighting/tile_shader.h"

//	Meyer's Singleton
//	https://laristra.github.io/flecsi/src/developer-guide/patterns/meyers_singleton.html

class Renderer {

public:

	static Renderer& instance() {
		static Renderer r;
		return r;
	}

	Renderer(const Renderer&) = delete;
	Renderer& operator = (const Renderer&) = delete;

private:

	Renderer();
	~Renderer();

	SimpleShader* simpleShader;
	TileShader* lightingShader;

public:
	SimpleShader* getSimpleShader();
	TileShader* getTileShader();

};
