#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

GLuint loadTexture(const char* path, GLenum format);
GLuint loadJpg(const char* path);
GLuint loadPng(const char* path);
