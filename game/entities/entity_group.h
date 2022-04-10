#pragma once

#include  "entity.h"
#include <vector>

class EntityGroup : public Entity {

protected:
	std::vector<Entity*> entities;

public:

	EntityGroup();
	virtual ~EntityGroup();

	void addEntity(Entity* entity);

	virtual bool init();
	virtual void update(float deltaTime = 1);
	virtual void render();
	virtual void handleKeyboard(int key, int scancode, int action, int mods);
	virtual void handleMouse(double xpos, double ypos);
};
