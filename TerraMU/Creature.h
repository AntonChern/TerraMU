#pragma once
#define GLM_FORCE_RADIANS
#include "Entity.h"
class Converter;
#include <list>
using namespace glm;
using namespace std;

class Creature {
protected:
	Entity* avatar;

	list<vec2>* way;
	vec2 initialPosition;
	float speed;
	float visibilityRadius;
public:
	Creature(Entity* avatar, float speed, float visibilityRadius) : avatar(avatar), speed(speed), visibilityRadius(visibilityRadius)
	{ initialPosition = vec2(avatar->getPosition().x, avatar->getPosition().y); };

	virtual bool isInMotion() { return this->way && !this->way->empty(); };
	virtual void hookGo(float coordX, float coordY);
	virtual void hookChangeCamera(vec2 step);
	virtual void hookUpdate();
	virtual void go(float coordX, float coordY);
	virtual void update(float deltaTime);
	virtual Entity* getAvatar() { return avatar; };
	virtual void nullWay();
	virtual void hookStopAnimation();

	virtual float getVisibilityRadius() { return this->visibilityRadius; };
	virtual vec2 getInitialPosition() { return initialPosition; };
};

