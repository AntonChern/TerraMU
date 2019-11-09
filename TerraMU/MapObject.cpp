#include "MapObject.h"

MapObject::~MapObject() {
	if (action) {
		delete action;
	}
}

void MapObject::interact(float x, float y) {
	action->setPosition(x, y);
	action->execute();
}