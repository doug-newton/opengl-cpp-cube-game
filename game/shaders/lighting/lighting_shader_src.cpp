#include "tile_shader.h"

const std::string TileShader::vertexSource = std::string(R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragPos;
out vec3 normal;
out vec2 texCoord;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	fragPos = vec3(model * vec4(aPos, 1.0));
	normal = aNormal;
	texCoord = aTexCoord;
};
)glsl");

const std::string TileShader::fragmentSource = std::string(R"glsl(
#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material material;

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

out vec4 FragColor;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

uniform vec3 objectColor;
uniform vec3 viewPos;
uniform sampler2D tileset;
uniform int tileIndex;

int tileSetDim = 2;

void main()
{
	int x = tileIndex % tileSetDim;
	int y = tileSetDim - tileIndex/tileSetDim - 1;
	vec2 sampleCoord = vec2(x * (1.0f/tileSetDim), y * (1.0f/tileSetDim)) + texCoord / tileSetDim;

	vec3 ambient = light.ambient * material.ambient * texture(tileset, sampleCoord).xyz;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result, 1);
};
)glsl");

