#pragma once
#include "Entity.h"
#include <iostream>
#include <queue>
using namespace std;

class Creature {
private:

protected:
	Entity* avatar;

	queue<vec2>* way = nullptr;
	vec3 initialPosition;
	float speed;

public:
	Creature(Entity* avatar, float speed) : avatar(avatar), speed(speed) {};

	virtual Entity* getAvatar() { return avatar; };
	virtual void go(float x, float y);

};