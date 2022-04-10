#include "entity.h"

Entity::Entity() {}
Entity::~Entity() {}
bool Entity::init() { return true; }
void Entity::update(float deltaTime) {}
void Entity::render() {}
void Entity::handleKeyboard(int key, int scancode, int action, int mods) {}
void Entity::handleMouse(double xpos, double ypos) {}
