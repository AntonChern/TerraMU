#pragma once
class GameController;
class Item;
class InventorySubscriber;
class Slot;
#include "Creature.h"
#include <vector>

class Player: public Creature {
private:
	Entity* destination;

	int strength = 26;
	int agility = 26;
	int vitality = 26;
	int energy = 26;

	int inventoryWidth = 5;
	int inventoryHeight = 4;
	vector<vector<Item*>> items = {};
	vector<vector<Slot*>> slots = {};

	InventorySubscriber* observer = nullptr;

	int hitTime = 0;
public:
	Player(Entity* avatar, float speed, float visibilityRadius, int maxHealth, Entity* destination);
	~Player();

	Entity* getDestination() { return this->destination; };
	void hookGo(float coordX, float coordY);
	void hookChangeCamera(vec2 step);
	void hookUpdate();
	void hookStopAnimation();

	int getStrength() { return strength; };
	int getAgility() { return agility; };
	int getVitality() { return vitality; };
	int getEnergy() { return energy; };

	Item* getItem(int x, int y);
	bool addItem(Item* item, int x, int y);
	bool addItem(Item* item);
	Item* popItem(int x, int y);

	int getInventoryWidth() { return inventoryWidth; };
	int getInventoryHeight() { return inventoryHeight; };

	void setInventorySubscriber(InventorySubscriber* subscriber) { observer = subscriber; };

	void setSlots(list<Slot*> slots);

	void hit();
};

