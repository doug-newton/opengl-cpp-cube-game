#include "entity.h"
#include "block.h"
#include <vector>

class Tilemap : public Entity {

private:
	std::vector<Block*> blocks;
	int length;
	int breadth;

public:
	Tilemap(int length, int breadth);
	~Tilemap();

	bool init();
	void render();

};
