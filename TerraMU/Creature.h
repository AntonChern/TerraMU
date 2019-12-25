#pragma once
#define GLM_FORCE_RADIANS
#include "Entity.h"
class Converter;
class Action;
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
	list<Action*> actions;

	int health;
	int maxHealth;
	bool isWithTask = false;
public:
	Creature(Entity* avatar, float speed, float visibilityRadius, int maxHealth) : avatar(avatar), speed(speed), visibilityRadius(visibilityRadius), maxHealth(maxHealth)
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
	virtual void addAction(Action* action) { actions.push_back(action); };
	virtual void setActions(list<Action*> actions);
	virtual void clearActions();
};

