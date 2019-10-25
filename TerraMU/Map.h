#pragma once
#include "Renderer.h"
#include "MapObject.h"
#include "TexturedModel.h"
#include "EntityBuilder.h"
#include "Tile.h"
#include <list>
#include <map>
#include <iostream>
using namespace std;

class Map {
private:
	int columns;
	int rows;

	const int cellWidth = 32;
	const int cellHeight = 32;

	Tile** base;
	Tile** hat;
	//list<int> textureIDs;
	//map<const char*, int> *textureIDs;
	map<Tile, Entity*> *entities = new map<Tile, Entity*>();
	//list<Entity*> *entities;

	//add mob spawners

	vec3 position;
	float rotationX;
	float rotationY;
	float rotationZ;
	float scale;

	void drawLayer(Tile** layer, float offset, Renderer* renderer, Loader* loader, StreamShader* shader);

protected:
	static map<Tile, MapObject> mapObjects;

public:
	Map(int columns, int rows, Tile** base, Tile** hat, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) : 
		columns(columns), rows(rows), base(base), hat(hat),
		position(position), rotationX(rotationX), rotationY(rotationY), rotationZ(rotationZ), scale(scale) {};

	Map(const char* sourcePath, vec3 position, float rotationX, float rotationY, float rotationZ, float scale);

	void draw(Renderer *renderer, Loader* loader, StreamShader* shader);
	Action getAction(float x, float y);

	vec3 getPosition() { return position; };
	float getRotationX() { return rotationX; };
	float getRotationY() { return rotationY; };
	float getRotationZ() { return rotationZ; };
	float getScale() { return scale; };

	void setPosition(float x, float y, float z) { position = vec3(x, y, z); };
	void setPosition(vec3 position) { this->position = position; };
	void setScale(float s) { scale = s; };
	void setRotationX(float r) { rotationX = r; };
	void setRotationY(float r) { rotationY = r; };
	void setRotationZ(float r) { rotationZ = r; };

	void increasePosition(float dx, float dy, float dz) { position += vec3(dx, dy, dz); };
	void increasePosition(vec3 dv) { position += dv; };
	void increaseScale(float ds) { scale += ds; };
	void increaseRotationX(float dr) { rotationX += dr; };
	void increaseRotationY(float dr) { rotationY += dr; };
	void increaseRotationZ(float dr) { rotationZ += dr; };

};