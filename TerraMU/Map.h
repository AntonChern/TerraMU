#pragma once
#include "Renderer.h"
class MapObject;
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

	map<Tile, Entity*> *entities = new map<Tile, Entity*>();
	static map<Tile, MapObject*> mapObjects;

	//add mob spawners and NPCs

	vec3 position;
	float rotationX;
	float rotationY;
	float rotationZ;
	vec3 scale;

	void drawLayer(Tile** layer, float offset, Renderer* renderer, Loader* loader, StreamShader* shader,
		float posX, float posY, int horyzontalSide, int verticalSide);

	MapObject* getMapObject(Tile tile);

public:
	Map(int columns, int rows, Tile** base, Tile** hat, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) : 
		columns(columns), rows(rows), base(base), hat(hat),
		position(position), rotationX(rotationX), rotationY(rotationY), rotationZ(rotationZ), scale(vec3(scale)) {};

	Map(int columns, int rows, Tile** base, Tile** hat, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
		columns(columns), rows(rows), base(base), hat(hat),
		position(position), rotationX(rotationX), rotationY(rotationY), rotationZ(rotationZ), scale(scale) {};

	Map(const char* sourcePath, vec3 position, float rotationX, float rotationY, float rotationZ, float scale);

	void drawRectangleArea(Renderer *renderer, Loader* loader, StreamShader* shader,
		float posX, float posY, int horyzontalSide, int verticalSide);

	int getColumns() { return columns; };
	int getRows() { return rows; };

	void interact(float x, float y);

	vec3 getPosition() { return position; };
	float getRotationX() { return rotationX; };
	float getRotationY() { return rotationY; };
	float getRotationZ() { return rotationZ; };
	vec3 getScale() { return scale; };

	void setPosition(float x, float y, float z) { position = vec3(x, y, z); };
	void setPosition(vec3 position) { this->position = position; };
	void setScale(vec3 s) { scale = s; };
	void setScale(float s) { scale = vec3(s); };
	void setScale(float xScale, float yScale, float zScale) { scale = vec3(xScale, yScale, zScale); };
	void setRotationX(float r) { rotationX = r; };
	void setRotationY(float r) { rotationY = r; };
	void setRotationZ(float r) { rotationZ = r; };

	void increasePosition(float dx, float dy, float dz) { position += vec3(dx, dy, dz); };
	void increasePosition(vec3 dv) { position += dv; };
	void increaseScale(vec3 ds) { scale += ds; };
	void increaseScale(float ds) { scale += vec3(ds); };
	void increaseScale(float dxScale, float dyScale, float dzScale) { scale += vec3(dxScale, dyScale, dzScale); };
	void increaseRotationX(float dr) { rotationX += dr; };
	void increaseRotationY(float dr) { rotationY += dr; };
	void increaseRotationZ(float dr) { rotationZ += dr; };

};

//map<Tile, MapObject> Map::mapObjects = {
//	{GRASS_0, MapObject(true, true, "grass_0.png", 32, 32)},
//	{GRASS_1, MapObject(true, true, "grass_1.png", 32, 32)},
//	{GRASS_2, MapObject(true, true, "grass_2.png", 32, 32)},
//	{STONE_0, MapObject(true, true, "stone_0.png", 32, 32)},
//	{STONE_1, MapObject(true, true, "stone_1.png", 32, 32)},
//	{STONE_2, MapObject(true, true, "stone_2.png", 32, 32)},
//	{STONE_3, MapObject(true, true, "stone_3.png", 32, 32)},
//	{STONE_4, MapObject(true, true, "stone_4.png", 32, 32)},
//	{MONUMENT, MapObject(false, true, "monument.png", 32, 64)}
//};