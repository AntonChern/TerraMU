#include "MobSpawner.h"
#include "GameController.h"
#include "AnimationPendulum.h"

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
		delete mob;
	}
}