#pragma once
class Player;
class Slot;
#include "Subscriber.h"
#include <vector>
#include <list>
using namespace std;

class InventorySubscriber : public Subscriber {
private:
	Player* player;
	vector<vector<Slot*>> slots = {};

public:
	InventorySubscriber(Player* player, list<Slot*> slots);

	void update();

};