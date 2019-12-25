#include "GrabAction.h"
#include "GameController.h"
#include "Gui.h"
#include "Item.h"

void GrabAction::execute() {
	GameController::getGui()->setGrabbedItem(target);
}

Item* GrabAction::getGrabbedItem() {
	return GameController::getGui()->getGrabbedItem();
}