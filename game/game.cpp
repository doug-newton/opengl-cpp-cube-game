#include "game.h"

Game* Game::instance = nullptr;

Game::Game()
	:
	window(nullptr),
	camera(nullptr),
	light(nullptr),
	EntityGroup()
{
	if (instance != nullptr)
		throw "Game can only be instantiated once";

	instance = this;

}

bool Game::init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	int width = 1280;
	int height = 960;

	window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	camera = new Camera(width, height);
	light = new Light(0, 5, 0);

	addEntity(camera);
	addEntity(light);
	addEntity(new Tilemap(25, 25));

	return EntityGroup::init();
}

void Game::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Renderer::instance().getSimpleShader()->use();

	Renderer::instance().getSimpleShader()->setProjection(camera->getProjectionMatrix());
	Renderer::instance().getSimpleShader()->setView(camera->getViewMatrix());

	Renderer::instance().getLightingShader()->use();
	Renderer::instance().getLightingShader()->setLight(light->getShaderLight());

	Renderer::instance().getLightingShader()->setProjection(camera->getProjectionMatrix());
	Renderer::instance().getLightingShader()->setView(camera->getViewMatrix());
	Renderer::instance().getLightingShader()->setViewPos(camera->getPosition());

	EntityGroup::render();
}

//	---------------------------------	//
//	----------- CALLBACKS -----------	//
//	---------------------------------	//

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void Game::setCallbacks() {
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);
}

void Game::handleWindowSizeChange(int w, int h) {
	camera->setWindowDimensions(w, h);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	Game::instance->handleWindowSizeChange(width, height);
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, true);
			break;
		}
	}

	Game::instance->handleKeyboard(key, scancode, action, mods);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	Game::instance->handleMouse(xpos, ypos);
}
