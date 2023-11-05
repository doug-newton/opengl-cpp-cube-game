#include "tilemap.h"

Tilemap::Tilemap(int length, int breadth) 
	:
	length(length), breadth(breadth),
	EntityGroup()
{
}

bool Tilemap::init() {
	float offsetX = -breadth / 2;
	float offsetZ = -length / 2;
	for (int x = 0; x < breadth; x++) {
		for (int z = 0; z < length; z++) {
			int type = rand() % 4;
			entities.push_back(new Tile(type, 
				offsetX + x, 
				0, 
				offsetZ + z));
		}
	}

	return EntityGroup::init();
}