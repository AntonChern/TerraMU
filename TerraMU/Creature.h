#pragma once
#include "Entity.h"
#include "Converter.h"
#include <queue>

class Creature {
protected:
	Entity* avatar;

	queue<vec2>* way;
	vec3 initialPosition;
	float speed;
public:
	Creature(Entity* avatar, float speed) : avatar(avatar), speed(speed) {};

	virtual bool isInMotion() { return this->way && !this->way->empty(); };
	virtual void hookGo(float coordX, float coordY);
	virtual void hookChangeCamera(vec3 step);
	virtual void hookUpdate();
	virtual void go(float coordX, float coordY);
	virtual void update(float deltaTime);
	virtual Entity* getAvatar() { return avatar; };
	virtual void nullWay();
	virtual void hookStopAnimation();
};

