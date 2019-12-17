#pragma once
#include "Entity.h"
#include "Converter.h"
#include <queue>

class Creature {
protected:
	Entity* avatar;

	list<vec2>* way;
	vec2 initialPosition;
	float speed;
	float visibilityRadius;

	int health;
	bool isWithTask = false;
public:
	Creature(Entity* avatar, float speed, float visibilityRadius) : avatar(avatar), speed(speed), visibilityRadius(visibilityRadius)
	{ initialPosition = vec2(avatar->getPosition().x, avatar->getPosition().y); };

	virtual bool isInMotion() { return this->way && !this->way->empty(); };
	virtual bool containsTask() { return this->isWithTask; };
	virtual void hookGo(float coordX, float coordY);
	virtual void hookChangeCamera(vec2 step);
	virtual void hookUpdate();
	virtual void go(float coordX, float coordY);
	virtual void shortGo(float coordX, float coordY);
	virtual void update(float deltaTime);
	virtual Entity* getAvatar() { return avatar; };
	virtual void nullWay();
	virtual void hookStopAnimation();
	virtual bool isDead() { return health <= 0; };

	virtual float getVisibilityRadius() { return this->visibilityRadius; };
	virtual vec2 getInitialPosition() { return initialPosition; };

	virtual void hit();
};

