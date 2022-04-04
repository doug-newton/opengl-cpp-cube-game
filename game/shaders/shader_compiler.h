#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ShaderCompiler {
public:
	static GLuint compileShaderProgram(const char* vertexSource, const char* fragmentSource);
};
