#include "game.h"
#include "../Camera.h"

Game* Game::instance = nullptr;

Game::Game()
	:
	entities(0),
	window(nullptr),
	texture0(0),
	texture1(0),
	vao(0),
	lightVao(0),
	camera(nullptr),
	material(
		glm::vec3(1.0f, 0.5f, 0.31f),
		glm::vec3(1.0f, 0.5f, 0.31f),
		glm::vec3(0.5f, 0.5f, 0.9f),
		32.0f),
	light(
		glm::vec3(-3.0f, 5.0f, -3.0f),
		glm::vec3(0.2f, 0.2f, 0.2f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 1.0f, 1.0f)
	),
	projection(glm::perspective(glm::radians(45.0f), 600.0f / 600.0f, 0.1f, 100.0f)),
	position(0.0f, 0.0f, -3.0f)
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

	addEntity(camera);

	texture0 = loadJpg("container.jpg");
	texture1 = loadPng("awesomeface.png");
	vao = createCubeWithNormals();
	lightVao = createLightVao();

	bool ok = true;

	for (auto it = entities.begin(); it != entities.end(); it++) {
		ok &= (*it)->init();
	}

	return ok;
}

void Game::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 view = camera->getViewMatrix();

	//	for the light itself, use the simple shader (don't apply lighting to it)

	Renderer::instance().getSimpleShader()->use();
	Renderer::instance().getSimpleShader()->setProjection(projection);
	Renderer::instance().getSimpleShader()->setView(view);

	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, light.position);
	lightModel = glm::scale(lightModel, glm::vec3(0.2f));

	Renderer::instance().getSimpleShader()->setObjectColor(lightColor);

	glBindVertexArray(lightVao);
	Renderer::instance().getSimpleShader()->setModel(lightModel);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	for (auto it = entities.begin(); it != entities.end(); it++) {
		(*it)->render();
	}

	//	for the rest of the objects, use the lighting shader (apply lighting)

	Renderer::instance().getLightingShader()->use();
	Renderer::instance().getLightingShader()->setLight(light);
	Renderer::instance().getLightingShader()->setProjection(projection);
	Renderer::instance().getLightingShader()->setView(view);
	Renderer::instance().getLightingShader()->setViewPos(camera->getPosition());

	//	draw all entities except the light

	Renderer::instance().getLightingShader()->setMaterial(material);
	glBindVertexArray(vao);
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, position);
	transform = glm::scale(transform, glm::vec3(3.0f, 3.0f, 3.0f));
	Renderer::instance().getLightingShader()->setModel(transform);
	glDrawArrays(GL_TRIANGLES, 0, 36);
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

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void Game::addEntity(Entity* entity) {
	entities.push_back(entity);
}

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
