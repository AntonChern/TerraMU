#include "MapObject.h"

MapObject::~MapObject() {
	/*if (action) {
		delete action;
	}*/
}

void MapObject::interact() {
	action->execute();
}