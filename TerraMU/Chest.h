#pragma once
#include "MapObject.h"

class Chest : public MapObject {
public:
	Chest() : MapObject(false, true, "chest.png", 32, 32) {};
	Action interact() { return OPEN_CHEST; };
};