#pragma once
#include "Entity.h"
#include <list>
#include <iostream>
using namespace std;

class Map {
private:
	Entity *base;
	char cells[8];
	list<Entity *> *objects;
	//add mob spawners

public:
	Map(list<Entity *> *objects, char cells[8]);
	bool isEmpty(int x, int y);

};