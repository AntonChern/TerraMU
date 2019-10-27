#pragma once
class Action;
#include "Action.h"

class MapObject {
private:
	Action* action;

	int width;
	int height;

	bool isVisible;
	const char* texturePath;

public:
	MapObject(Action* action, bool isVisible, const char *texturePath, int width, int height) :
		action(action), isVisible(isVisible), texturePath(texturePath), width(width), height(height) {};
	~MapObject();

	bool getIsVisible() { return isVisible; };
	const char* getTexturePath() { return texturePath; };

	int getWidth() { return width; };
	int getHeight() { return height; };

	void interact();

};