#include "entity_group.h"
#include "tile.h"
#include <vector>

class Tilemap : public EntityGroup {

private:
	int length;
	int breadth;

public:
	Tilemap(int length, int breadth);
	bool init();
};
