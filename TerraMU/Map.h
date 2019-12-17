#pragma once
#define GLM_FORCE_RADIANS
class Renderer;
class MapObject;
class MobSpawner;
class Item;
class GuiElement;
class Entity;
enum Tile;
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
	bool** mobMap = nullptr;

	static map<Tile, MapObject*> mapObjects;
	list<Entity*> entities;

	list<Item*> items;

	//add NPCs

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
	list<GuiElement*> getTitles(float posX, float posY, int horyzontalSide, int verticalSide);

	void addItem(Item* item, float x, float y);

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