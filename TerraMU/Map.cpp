#include "Map.h"

Map::Map(list<Entity*>* objects, char cells[8]) : objects(objects) {
	for (int i = 0; i < 8; i++) {
		this->cells[i] = cells[i];
	}
}

bool Map::isEmpty(int x, int y) {
	char maskX = 0b10000000;
	for (int i = 0; i < x; i++) {
		maskX >>= 1;
	}

	return cells[y] ^ maskX;
 }