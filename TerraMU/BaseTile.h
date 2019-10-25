#pragma once
#include "MapObject.h"

class BaseTile : public MapObject {
public:
	BaseTile(const char* texturePath) : MapObject::MapObject(true, true, texturePath, 32, 32) {};
};