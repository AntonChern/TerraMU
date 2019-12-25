#include "MobSpawner.h"
#include "GameController.h"
#include "AnimationPendulum.h"
#include "EntityFactory.h"
#include "Monster.h"
#include "Map.h"
#include "Item.h"
#include "Converter.h"

void MobSpawner::update(float deltaTime) {
	if (mobs->size() < maxNumOfMobs) {
		if (time >= spawnPeriod) {
			time = 0;

			Entity* avatar = EntityFactory::createEntity(texturePath,
				new AnimationPendulum(numberOfTimes, animationPeriod, animationPosition, animationScale, offset),
				position, rotationX, rotationY, rotationZ, scale);

			Monster* newMonster = new Monster(avatar, speed, visibilityRadius, maxHealth, isAnimated, movingProbability, movingPeriod);

			mobs->push_back(newMonster);
		}
		time += deltaTime;
	}
	list<Monster*> dead = {};
	for (Monster* mob : *mobs) {
		mob->update(deltaTime);
		if (mob->isDead()) {
			dead.push_front(mob);
		}
	}
	for (Monster* mob : dead) {
		mobs->remove(mob);
		vec2 position = Converter::fromOpenGLToMap(vec2(mob->getAvatar()->getPosition().x, mob->getAvatar()->getPosition().y - (float)mob->getAvatar()->getScale().y / 2));
		float randValue = ((float)rand() / (RAND_MAX));
		Item* loot = nullptr;
		if (randValue < 0.5f) {
			loot = new Item("apple.png", "Apple");
		} else {
			loot = new Item("book.png", "Book");
		}
		GameController::getMap()->addItem(loot, position.x, position.y);
		delete mob;
	}
}