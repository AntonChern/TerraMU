#include "GoAction.h"
#include "GameController.h"
#include "Player.h"

void GoAction::execute() {
	GameController::getPlayer()->go(coordX, coordY);
}