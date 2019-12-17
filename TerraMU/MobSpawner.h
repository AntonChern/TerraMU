#pragma once
class Monster;
#include "Monster.h"

class MobSpawner {
private:
	float speed;
	float visibilityRadius;
	int maxHealth;
	float movingProbability;
	int movingPeriod;
	char const* texturePath;
	float numberOfTimes;
	float animationPeriod;
	vec2 animationPosition;
	vec2 animationScale;
	float offset;
	vec3 position;
	float rotationX;
	float rotationY;
	float rotationZ;
	float scale;

	float spawnPeriod;
	float time;
	list<Monster*>* mobs;
	int maxNumOfMobs;
	bool isAnimated;
public:
	MobSpawner(char const texturePath[],
		float numberOfTimes, float animationPeriod, vec2 animationPosition, vec2 animationScale, float offset,
		vec3 position, float rotationX, float rotationY, float rotationZ, float scale,
		float speed, bool isAnimated, float visibilityRadius, int maxHealth, float movingProbability, int movingPeriod,
		float spawnPeriod, int maxNumOfMobs) :
		texturePath(texturePath),
		numberOfTimes(numberOfTimes), animationPeriod(animationPeriod), animationPosition(animationPosition), animationScale(animationScale), offset(offset),
		position(position), rotationX(rotationX), rotationY(rotationY), rotationZ(rotationZ), scale(scale),
		speed(speed), isAnimated(isAnimated), visibilityRadius(visibilityRadius), maxHealth(maxHealth), movingProbability(movingProbability), movingPeriod(movingPeriod),
		spawnPeriod(spawnPeriod), maxNumOfMobs(maxNumOfMobs) { mobs = new list<Monster*>; time = spawnPeriod; };
	
	list<Monster*>* getMobs() { return this->mobs; };
	void update(float deltaTime);
};

