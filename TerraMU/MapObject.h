#pragma once
class Action;

class MapObject {
private:
	Action* action;

	int width;
	int height;

	bool isReachable;
	const char* texturePath;

public:
	MapObject(Action* action, bool isReachable, const char *texturePath, int width, int height) :
		action(action), isReachable(isReachable), texturePath(texturePath), width(width), height(height) {};
	~MapObject();

	bool getIsReachable() { return isReachable; };
	const char* getTexturePath() { return texturePath; };

	int getWidth() { return width; };
	int getHeight() { return height; };

	void interact(float x, float y);
};