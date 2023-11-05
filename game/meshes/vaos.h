#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLuint createTexturedQuadVao();
GLuint createTexturedCubeWithoutEbo();
GLuint createCubeWithNormals();
GLuint createCubeWithNormalsAndTexCoords();
GLuint createLightVao();
GLuint createPlaneWithNormalsAndTexCoords();
