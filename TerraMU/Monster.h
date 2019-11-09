#pragma once
#include "Creature.h"

class Monster: public Creature {
public:
	Monster(Entity* avatar, float speed) : Creature(avatar, speed) {};
};

