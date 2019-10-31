#pragma once
class Action;
#include "Action.h"

class MapObject {
private:
	Action* action;

	int width;
	int height;

	bool isReachable;
	bool isVisible;
	const char* texturePath;

public:
	MapObject(Action* action, bool isReachable, bool isVisible, const char *texturePath, int width, int height) :
		action(action), isReachable(isReachable), isVisible(isVisible), texturePath(texturePath), width(width), height(height) {};
	~MapObject();

	bool getIsReachable() { return isReachable; };
	bool getIsVisible() { return isVisible; };
	const char* getTexturePath() { return texturePath; };

	int getWidth() { return width; };
	int getHeight() { return height; };

	void interact(float x, float y);
};