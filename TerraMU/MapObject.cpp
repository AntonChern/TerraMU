#include "MapObject.h"
#include "Action.h"
#include "GameController.h"

MapObject::~MapObject() {
	if (action) {
		delete action;
	}
}

void MapObject::interact(float x, float y) {
	action->setPosition(x, y);
	GameController::setActions({action});
}