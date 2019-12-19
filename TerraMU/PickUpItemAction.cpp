#include "PickUpItemAction.h"
#include "Item.h"
#include "GameController.h"
#include "Map.h"
#include "Entity.h"
#include "Player.h"

void PickUpItemAction::execute() {
	GameController::getMap()->removeItem(item);
	GameController::getPlayer()->addItem(item);
}