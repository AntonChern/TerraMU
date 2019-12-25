#include "Player.h"
#include "Converter.h"
#include "Camera.h"
#include "GameController.h"
#include "Animation.h"
#include "InventorySubscriber.h"
#include "Slot.h"

Player::Player(Entity* avatar, float speed, float visibilityRadius, int maxHealth, Entity* destination)
	: Creature(avatar, speed, visibilityRadius, maxHealth), destination(destination) {
	for (int i = 0; i < inventoryWidth; i++) {
		items.push_back({});
		for (int j = 0; j < inventoryHeight; j++) {
			items.at(i).push_back(nullptr);
		}
	}

	health = maxHealth;
}

Player::~Player() {
	if (observer) {
		delete observer;
	}
}

void Player::hookGo(float coordX, float coordY) {
	destination->getAnimation()->reset();
	destination->getAnimation()->play();

	vec2 whither = Converter::fromMapToOpenGL(vec2(coordX, coordY));
	destination->setPosition(whither.x, whither.y, destination->getPosition().z);
}

void Player::hookChangeCamera(vec2 step) {
	GameController::getCamera()->increasePosition(step.x, step.y, 0);
}

void Player::hookUpdate() {
	if (isDead()) {
		nullWay();
		health = maxHealth;
		hitTime = 0;
		avatar->setPosition(0.0f, 0.0f, 0.065f);
		GameController::getCamera()->setPosition(avatar->getPosition().x, avatar->getPosition().y, 1);
	}

	if (!isInMotion()) {
		destination->getAnimation()->stop();
	}
}

void Player::hookStopAnimation() {
	avatar->getAnimation()->stop();
	avatar->getAnimation()->reset();
}

Item* Player::getItem(int x, int y) {
	//return items.at(x).at(y);
	return slots.at(x).at(y)->getItem();
}

bool Player::addItem(Item* item, int x, int y) {
	/*if (getItem(x, y)) {
		return false;
	}

	vector<Item*> res = {};
	for (int i = 0; i < y; i++) {
		res.push_back(items.at(x).at(i));
	}
	res.push_back(item);
	for (int i = y + 1; i < inventoryHeight; i++) {
		res.push_back(items.at(x).at(i));
	}
	items.at(x) = res;

	if (observer) {
		observer->update();
	}
	return true;*/
	if (getItem(x, y)) {
		return false;
	}

	slots.at(x).at(y)->setItem(item);
	
	return true;
}

bool Player::addItem(Item* item) {
	/*int i = 0;
	for (vector<Item*> column : items) {
		int j = 0;
		for (Item* curItem : column) {
			if (!curItem) {
				addItem(item, i, j);
				return true;
			}
			j++;
		}
		i++;
	}

	return false;*/
	int i = 0;
	for (vector<Slot*> column : slots) {
		int j = 0;
		for (Slot* curSlot : column) {
			if (!curSlot->getItem()) {
				addItem(item, i, j);
				return true;
			}
			j++;
		}
		i++;
	}

	return false;
}

Item* Player::popItem(int x, int y) {
	/*Item* result = getItem(x, y);

	vector<Item*> res = {};
	for (int i = 0; i < y; i++) {
		res.push_back(items.at(x).at(i));
	}
	res.push_back(nullptr);
	for (int i = y + 1; i < inventoryHeight; i++) {
		res.push_back(items.at(x).at(i));
	}
	items.at(x) = res;

	if (observer) {
		observer->update();
	}
	return result;*/
	Item* result = getItem(x, y);
	slots.at(x).at(y)->setItem(nullptr);
	return result;
}

void Player::setSlots(list<Slot*> slots) {
	for (int i = 0; i < inventoryWidth; i++) {
		this->slots.push_back({});
		for (int j = 0; j < inventoryHeight; j++) {
			this->slots.at(i).push_back(slots.front());
			slots.pop_front();
		}
	}
}

void Player::hit() {
	if (hitTime == 100) {
		hitTime = 0;
		health -= 10;
	}
	hitTime++;
}