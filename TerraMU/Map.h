#pragma once
#include "Renderer.h"
class MapObject;
class MobSpawner;
#include "MapObject.h"
#include "TexturedModel.h"
#include "EntityFactory.h"
#include "Tile.h"
#include "Loader.h"
#include "Moveable.h"
#include "MobSpawner.h"
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
	bool** mobMap = nullptr;

	static map<Tile, MapObject*> mapObjects;
	list<Entity*> entities;

	//add mob spawners and NPCs

	void processLayer(Tile** layer, float offset, float posX, float posY, int horyzontalSide, int verticalSide);

	MapObject* getMapObject(Tile tile);

	Tile getTile(int x, int y);

	list<MobSpawner*>* spawners;

public:
	Map(int columns, int rows, Tile** base, Tile** hat, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
		Moveable(position, rotationX, rotationY, rotationZ, scale),
		columns(columns), rows(rows), base(base), hat(hat) {};

	Map(int columns, int rows, Tile** base, Tile** hat, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
		Moveable(position, rotationX, rotationY, rotationZ, scale),
		columns(columns), rows(rows), base(base), hat(hat) {};

	Map(const char* sourcePath, vec3 position, float rotationX, float rotationY, float rotationZ, float scale);

	~Map();

	list<Entity*> getRectangleArea(float posX, float posY, int horyzontalSide, int verticalSide);

	int getColumns() { return columns; };
	int getRows() { return rows; };

	void interact(float x, float y);

	bool** getReachMap() { return reachMap; };
	bool** getMobMap() { return mobMap; };
	void markMob(Entity* mobAvatar);
	void nullMobMap();
	void addMobSpawner(MobSpawner* spawner) { spawners->push_front(spawner); };
	void updateMobMap();
	list<MobSpawner*>* getSpawners() { return spawners; };
};