#include "ShortGoAction.h"
#include "GameController.h"

void ShortGoAction::execute() {
	GameController::shortGo(coordX, coordY);
}