#include "HitAction.h"
#include "GameController.h"

void HitAction::execute() {
	this->target->hit();
}