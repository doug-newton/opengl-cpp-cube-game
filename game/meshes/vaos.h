#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vao_reference.h"
#include <memory>

std::shared_ptr<VaoReference> createCubeVao();
std::shared_ptr<VaoReference> createTileVao();
