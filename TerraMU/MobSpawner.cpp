#include "MobSpawner.h"
#include "GameController.h"
#include "AnimationPendulum.h"
#include "EntityFactory.h"
#include "Monster.h"

void MobSpawner::update() {
	if (mobs->size() < maxNumOfMobs) {
		if (time == spawnPeriod) {
			time = 0;

			Entity* avatar = EntityFactory::createEntity(texturePath,
				new AnimationPendulum(numberOfTimes, animationPeriod, animationPosition, animationScale, offset),
				position, rotationX, rotationY, rotationZ, scale);

			Monster* newMonster = new Monster(avatar, speed, visibilityRadius, isAnimated,  movingProbability, movingPeriod);

			mobs->push_back(newMonster);
		}
		time++;
	}
}