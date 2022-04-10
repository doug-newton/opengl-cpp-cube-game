#include "entity_group.h"

EntityGroup::EntityGroup()
	:
	entities(0) {

}

EntityGroup::~EntityGroup() {
	for (auto it = entities.begin(); it != entities.end(); it++) {
		delete (*it);
	}
}

void EntityGroup::addEntity(Entity* entity) {
	entities.push_back(entity);
}

bool EntityGroup::init() {
	bool ok = true;
	for (auto it = entities.begin(); it != entities.end(); it++) {
		ok &= (*it)->init();
	}
	return ok;
}

void EntityGroup::update(float deltaTime) {
	for (auto it = entities.begin(); it != entities.end(); it++) {
		(*it)->update(deltaTime);
	}
}

void EntityGroup::render() {
	for (auto it = entities.begin(); it != entities.end(); it++) {
		(*it)->render();
	}
}

void EntityGroup::handleKeyboard(int key, int scancode, int action, int mods) {
	for (auto it = entities.begin(); it != entities.end(); it++) {
		(*it)->handleKeyboard(key, scancode, action, mods);
	}
}

void EntityGroup::handleMouse(double xpos, double ypos) {
	for (auto it = entities.begin(); it != entities.end(); it++) {
		(*it)->handleMouse(xpos, ypos);
	}
}