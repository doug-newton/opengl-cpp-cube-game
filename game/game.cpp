#include "game.h"
#include "../Camera.h"

Game* Game::instance = nullptr;

Game::Game()
	:
	entities(0),
	window(nullptr),
	camera(nullptr),
	light(nullptr),
	block(nullptr),
	projection(glm::perspective(glm::radians(45.0f), 600.0f / 600.0f, 0.1f, 100.0f))
{
	if (instance != nullptr)
		throw "Game can only be instantiated once";

	instance = this;

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 600.0f / 600.0f, 0.1f, 100.0f);
	glm::vec3 position(0.0f, 0.0f, -3.0f);
}

bool Game::init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(600, 600, "LearnOpenGL", NULL, NULL);
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

	glViewport(0, 0, 600, 600);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	camera = new Camera;
	light = new Light;
	block = new Block;

	addEntity(camera);
	addEntity(light);
	addEntity(block);

	bool ok = true;

	for (auto it = entities.begin(); it != entities.end(); it++) {
		ok &= (*it)->init();
	}

	return ok;
}

void Game::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 view = camera->getViewMatrix();

	Renderer::instance().getSimpleShader()->use();
	Renderer::instance().getSimpleShader()->setProjection(projection);
	Renderer::instance().getSimpleShader()->setView(view);

	Renderer::instance().getLightingShader()->use();
	Renderer::instance().getLightingShader()->setLight(light->getShaderLight());
	Renderer::instance().getLightingShader()->setProjection(projection);
	Renderer::instance().getLightingShader()->setView(view);
	Renderer::instance().getLightingShader()->setViewPos(camera->getPosition());

	for (auto it = entities.begin(); it != entities.end(); it++) {
		(*it)->render();
	}
}

Game::~Game() {
	for (auto it = entities.begin(); it != entities.end(); it++) {
		delete (*it);
	}
}

void Game::update(float deltaTime) {
	for (auto it = entities.begin(); it != entities.end(); it++) {
		(*it)->update(deltaTime);
	}
}

void Game::handleKeyboard(int key, int scancode, int action, int mods) {
	for (auto it = entities.begin(); it != entities.end(); it++) {
		(*it)->handleKeyboard(key, scancode, action, mods);
	}
}

void Game::handleMouse(double xpos, double ypos) {
	for (auto it = entities.begin(); it != entities.end(); it++) {
		(*it)->handleMouse(xpos, ypos);
	}
}

void Game::addEntity(Entity* entity) {
	entities.push_back(entity);
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
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
