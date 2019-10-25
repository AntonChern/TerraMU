#pragma once
#include "Action.h"

class MapObject {
protected:
	int width;
	int height;

	bool isReachable;
	bool isVisible;
	const char* texturePath;

public:
	MapObject(bool isReachable, bool isVisible, const char *texturePath, int width, int height) :
		isReachable(isReachable), isVisible(isVisible), texturePath(texturePath), width(width), height(height) {};
	bool getIsReachable() { return isReachable; };
	bool getIsVisible() { return isVisible; };
	const char* getTexturePath() { return texturePath; };

	int getWidth() { return width; };
	int getHeight() { return height; };

	Action interact();

};