#pragma once
#include "GameController.h"
#include "Creature.h"

class Player: public Creature {
private:
	Entity* destination;
public:
	Player(Entity* avatar, float speed, float visibilityRadius, Entity* destination) : Creature(avatar, speed, visibilityRadius), destination(destination) {};

	Entity* getDestination() { return this->destination; };
	void hookGo(float coordX, float coordY);
	void hookChangeCamera(vec2 step);
	void hookUpdate();
	void hookStopAnimation();
};

