#pragma once

class ModelTexture {
private:
	int textureID;
public:
	ModelTexture(int textureID) : textureID(textureID) {};
	int getID() { return textureID; };
};