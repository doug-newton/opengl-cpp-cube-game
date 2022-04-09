#pragma once

class Entity {
public:
	virtual bool init();
	virtual void update(float deltaTime = 1);
	virtual void render();
	virtual void handleKeyboard(int key, int scancode, int action, int mods);
	virtual void handleMouse(double xpos, double ypos);
};

