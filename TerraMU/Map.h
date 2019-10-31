#pragma once
#include "Renderer.h"
class MapObject;
#include "MapObject.h"
#include "TexturedModel.h"
#include "EntityBuilder.h"
#include "Tile.h"
#include "Moveable.h"
#include <list>
#include <map>
#include <iostream>
using namespace std;

class Map : public Moveable {
private:
	int columns;
	int rows;

	const int cellWidth = 32;
	const int cellHeight = 32;

	Tile** base;
	Tile** hat;

	bool** reachMap = nullptr;

	map<Tile, Entity*> *entities = new map<Tile, Entity*>();
	static map<Tile, MapObject*> mapObjects;

	//add mob spawners and NPCs

	void drawLayer(Tile** layer, float offset, Renderer* renderer, Loader* loader, StreamShader* shader,
		float posX, float posY, int horyzontalSide, int verticalSide);

	MapObject* getMapObject(Tile tile);

public:
	Map(int columns, int rows, Tile** base, Tile** hat, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
		Moveable(position, rotationX, rotationY, rotationZ, scale),
		columns(columns), rows(rows), base(base), hat(hat) {};

	Map(int columns, int rows, Tile** base, Tile** hat, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
		Moveable(position, rotationX, rotationY, rotationZ, scale),
		columns(columns), rows(rows), base(base), hat(hat) {};

	Map(const char* sourcePath, vec3 position, float rotationX, float rotationY, float rotationZ, float scale);

	~Map();

	void drawRectangleArea(Renderer *renderer, Loader* loader, StreamShader* shader,
		float posX, float posY, int horyzontalSide, int verticalSide);

	int getColumns() { return columns; };
	int getRows() { return rows; };

	void interact(float x, float y);

	bool** getReachMap();

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