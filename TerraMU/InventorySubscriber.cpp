#include "InventorySubscriber.h"
#include "Slot.h"
#include "Player.h"
#include "GameController.h"

InventorySubscriber::InventorySubscriber(Player* player, list<Slot*> slots) : player(player) {
	int inventoryWidth = GameController::getPlayer()->getInventoryWidth();
	int inventoryHeight = GameController::getPlayer()->getInventoryHeight();
	for (int i = 0; i < inventoryWidth; i++) {
		this->slots.push_back({});
		for (int j = 0; j < inventoryHeight; j++) {
			this->slots.at(i).push_back(slots.front());
			slots.pop_front();
		}
	}
}

void InventorySubscriber::update() {
	int i = 0;
	for (vector<Slot*> column : slots) {
		int j = 0;
		for (Slot* slot : column) {
			slot->setItem(player->getItem(i, j));
			j++;
		}
		i++;
	}
}