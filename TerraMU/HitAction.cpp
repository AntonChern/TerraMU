#include "HitAction.h"
#include "GameController.h"

void HitAction::execute() {
	target->hit();
}