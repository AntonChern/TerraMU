#pragma once
#include "MapObject.h"

class Monument : public MapObject {
public:
	Monument() : MapObject::MapObject(false, true, "monument.png", 32, 64) {};

};
