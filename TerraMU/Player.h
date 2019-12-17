#pragma once
#include "GameController.h"
#include "Creature.h"

class Player: public Creature {
private:
	Entity* destination;

	int strength = 26;
	int agility = 26;
	int vitality = 26;
	int energy = 26;
public:
	Player(Entity* avatar, float speed, float visibilityRadius, Entity* destination) : Creature(avatar, speed, visibilityRadius), destination(destination) {};

	Entity* getDestination() { return this->destination; };
	void hookGo(float coordX, float coordY);
	void hookChangeCamera(vec2 step);
	void hookUpdate();
	void hookStopAnimation();

	int getStrength() { return strength; };
	int getAgility() { return agility; };
	int getVitality() { return vitality; };
	int getEnergy() { return energy; };
};

