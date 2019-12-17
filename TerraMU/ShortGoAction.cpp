#include "ShortGoAction.h"
#include "GameController.h"
#include "Player.h"

void ShortGoAction::execute() {
	GameController::getPlayer()->shortGo(coordX, coordY);
}