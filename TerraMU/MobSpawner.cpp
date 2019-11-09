#include "MobSpawner.h"

void MobSpawner::update() {
	if (mobs->size() < maxNumOfMobs) {
		if (time == spawnPeriod * 20) {
			time = 0;

			Entity* avatar = EntityFactory::createEntity(texturePath,
				new AnimationPendulum(numberOfTimes, animationPeriod, animationPosition, animationScale, offset),
				position, rotationX, rotationY, rotationZ, scale);

			Monster* newMonster = new Monster(avatar, speed, isAnimated, visibilityRadius, movingProbability, movingPeriod);

			mobs->push_back(newMonster);
		}
		time++;
	}
}