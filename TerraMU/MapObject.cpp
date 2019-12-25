#include "MapObject.h"
#include "Action.h"
#include "GameController.h"
#include "Player.h"

MapObject::~MapObject() {
	if (action) {
		delete action;
	}
}

void MapObject::interact(float x, float y) {
	action->setPosition(x, y);
	GameController::getPlayer()->setActions({action});
}