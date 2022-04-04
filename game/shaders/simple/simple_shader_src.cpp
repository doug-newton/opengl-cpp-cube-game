#include "simple_shader.h"

const std::string SimpleShader::vertexSource = std::string(R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
};
)glsl");

const std::string SimpleShader::fragmentSource = std::string(R"glsl(
#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;

void main()
{
	FragColor = vec4(objectColor, 1);
};
)glsl");
