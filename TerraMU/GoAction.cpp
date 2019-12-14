#include "GoAction.h"
#include "GameController.h"

void GoAction::execute() {
	GameController::getPlayer()->go(coordX, coordY);
}