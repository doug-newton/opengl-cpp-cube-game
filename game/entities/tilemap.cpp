#include "tilemap.h"

Tilemap::Tilemap(int length, int breadth) 
	:
	length(length), breadth(breadth),
	blocks(0)
{
}

Tilemap::~Tilemap() {
	for (auto it = blocks.begin(); it != blocks.end(); it++) {
		delete (*it);
	}
}

bool Tilemap::init() {
	float offsetX = -breadth / 2;
	float offsetZ = -length / 2;
	for (int x = 0; x < breadth; x++) {
		for (int z = 0; z < length; z++) {
			int type = rand() % 4;
			blocks.push_back(new Block(type, 
				offsetX + x, 
				0, 
				offsetZ + z));
		}
	}

	bool ok = true;

	for (auto it = blocks.begin(); it != blocks.end(); it++) {
		ok &= (*it)->init();
	}

	return ok;
}

void Tilemap::render() {
	for (auto it = blocks.begin(); it != blocks.end(); it++) {
		(*it)->render();
	}
}