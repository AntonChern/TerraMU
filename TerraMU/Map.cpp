#include "Map.h"
#include "Tile.h"
#include "Converter.h"
#include "Monster.h"
#include "FramedLabel.h"
#include "DroppedItem.h"
#include "MapObject.h"
#include "MobSpawner.h"
#include "Item.h"
#include "EntityFactory.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

Map::Map(const char* sourcePath, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) :
	Moveable(position, rotationX, rotationY, rotationZ, scale) {
	ifstream fin(sourcePath);
	fin >> columns;
	fin >> rows;

	base = new Tile*[columns];
	for (int i = 0; i < columns; i++) {
		base[i] = new Tile[rows];
	}
	hat = new Tile*[columns];
	for (int i = 0; i < columns; i++) {
		hat[i] = new Tile[rows];
	}

	int size = columns * rows;
	string str;
	getline(fin, str);
	for (int j = 0; j < rows; j++) {
		getline(fin, str);
		for (int i = 0; i < columns; i++) {
			int tile = str.at(i) - ' ';
			base[i][j] = (Tile)tile;
		}
	}

	getline(fin, str);

	for (int j = 0; j < rows; j++) {
		getline(fin, str);
		for (int i = 0; i < columns; i++) {
			int tile = str.at(i) - ' ';
			hat[i][j] = (Tile)tile;
		}
	}

	/*for (int j = 0; j < rows; j++) {
		for (int i = 0; i < columns; i++) {
			int tile;
			fin >> tile;
			base[i][j] = (Tile)tile;
		}
	}

	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < columns; i++) {
			int tile;
			fin >> tile;
			hat[i][j] = (Tile)tile;
		}
	}*/
	fin.close();

	reachMap = new bool* [columns];
	for (int i = 0; i < columns; i++) {
		reachMap[i] = new bool[rows];
	}

	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			Tile currTile = hat[i][j];
			if (currTile == EMPTY) {
				currTile = base[i][j];
			}
			MapObject* currMapObject = getMapObject(currTile);
			if (currMapObject == nullptr) {
				reachMap[i][j] = false;
			}
			else {
				reachMap[i][j] = currMapObject->getIsReachable();
			}
		}
	}

	mobMap = new bool* [columns];
	for (int i = 0; i < columns; i++) {
		mobMap[i] = new bool[rows];
		for (int j = 0; j < rows; j++) {
			mobMap[i][j] = true;
		}
	}

	spawners = new list<MobSpawner*>();
}

void Map::processLayer(Tile** layer, float offset, float posX, float posY, int horyzontalSide, int verticalSide) {
	horyzontalSide += (horyzontalSide + 1) % 2;
	verticalSide += (verticalSide + 1) % 2;

	int startX = (int)(posX) - horyzontalSide / 2;
	int startY = (int)(posY) - verticalSide / 2;

	int endX = (int)(posX) + horyzontalSide / 2;
	int endY = (int)(posY) + verticalSide / 2;

	for (int j = max(0, startY); j < rows && j <= endY; j++) {
		for (int i = max(0, startX); i < columns && i <= endX; i++) {
			Tile currTile = layer[i][j];

			if (currTile == EMPTY) {
				continue;
			}

			MapObject* currMapObject = getMapObject(currTile);
			if (!currMapObject) {
				continue;
			}

			vec3 currPosition = vec3(position.x + scale.x * ((float)(2 * i + 1) / columns - 1) / 2,
				position.y + scale.y * ((-2 * (j + 1) + (float)currMapObject->getHeight() / cellHeight) / rows + 1) / 2,
				offset * (j + 1));

			vec3 currScale = vec3(this->scale.x * currMapObject->getWidth() / (columns * cellWidth),
				this->scale.y * currMapObject->getHeight() / (rows * cellHeight), 1.0f);

			Entity* currEntity = EntityFactory::createEntity(currMapObject->getTexturePath(),
				currPosition, this->rotationX, this->rotationY, this->rotationZ, currScale);

			entities.push_back(currEntity);
		}
	}
}

list<Entity*> Map::getRectangleArea(float posX, float posY, int horyzontalSide, int verticalSide) {
	EntityFactory::cleanEntities(entities);
	entities.clear();
	processLayer(base, 0.0f, posX, posY, horyzontalSide, verticalSide);
	processLayer(hat, 0.001f, posX, posY, horyzontalSide, verticalSide);

	list<Entity*> mapItems = {};

	for (Item* item : items) {
		vec3 pos = item->getDropped()->getPosition();
		vec2 pos2D = Converter::fromOpenGLToMap(vec2(pos.x, pos.y));
		if (pos2D.x < posX + horyzontalSide && pos2D.x > posX - horyzontalSide && pos2D.y < posY + verticalSide && pos2D.y > posY - verticalSide) {
			mapItems.push_back(item->getDropped()->getEntity());
		}
	}

	list<Entity*> result = {};
	for (Entity* entity : entities) {
		result.push_back(entity);
	}
	for (Entity* entity : mapItems) {
		result.push_back(entity);
	}

	return result;
}

Map::~Map() {
	if (reachMap) {
		for (int i = 0; i < columns; i++) {
			delete[] reachMap[i];
		}
		delete[] reachMap;
	}

	if (base) {
		for (int i = 0; i < columns; i++) {
			delete[] base[i];
		}
		delete[] base;
	}

	if (hat) {
		for (int i = 0; i < columns; i++) {
			delete[] hat[i];
		}
		delete[] hat;
	}

	delete spawners;
}

MapObject* Map::getMapObject(Tile tile) {
	try {
		return mapObjects.at(tile);
	}
	catch (const out_of_range & exc) {
		cerr << "Out of Range error: " << exc.what() << endl;
		cerr << "Map::mapObjects doesn't contain this Tile: " << tile << endl;
		return nullptr;
	}
}

Tile Map::getTile(int x, int y) {
	Tile tile = hat[x][y];
	if (tile == EMPTY) {
		tile = base[x][y];
	}
	return tile;
}

void Map::interact(float x, float y) {
	if (x < 0 || x >= columns || y < 0 || y >= rows) {
		return;
	}

  for (MobSpawner* spawner : *spawners) {
		for (Monster* mob : *spawner->getMobs()) {
			vec3 position = mob->getAvatar()->getPosition();
			float scaleX = mob->getAvatar()->getScale().x;
			float scaleY = mob->getAvatar()->getScale().y;
			vec2 mouse = Converter::fromMapToOpenGL(vec2(x, y));
			if ((mouse.x > position.x - (float)scaleX / 2 && mouse.x < position.x + (float)scaleX / 2) && (mouse.y > position.y - (float)scaleY / 2 && mouse.y < position.y + (float)scaleY / 2)) {
				vec2 mapPosition = Converter::fromOpenGLToMap(vec2(position.x, position.y - (float)mob->getAvatar()->getScale().y / 2));
				mob->interact(mapPosition.x, mapPosition.y);
				return;
			}
		}
	}

	for (Item* item : items) {
		vec3 pos = item->getDropped()->getPosition();
		vec2 click = Converter::fromMapToOpenGL(vec2(x, y));
		if (click.x < pos.x + item->getDropped()->getScale().x && click.x > pos.x - item->getDropped()->getScale().x &&
			click.y < pos.y + item->getDropped()->getScale().y && click.y > pos.y - item->getDropped()->getScale().y) {
			item->interact();
			return;
    }
  }

	int coordX = (int)x;
	int coordY = (int)y;

	Tile tile = getTile(coordX, coordY);
	MapObject* mapObject = getMapObject(tile);

	if ((float)x - (coordX + 0.5f) > 0) {
		if (coordX + 1 < columns && !reachMap[coordX + 1][coordY]) {
			x = coordX + 0.5f;
		}
	} else {
		if (coordX - 1 >= 0 && !reachMap[coordX - 1][coordY]) {
			x = coordX + 0.5f;
		}
	}

	mapObject->interact(x, y);
}

void Map::markMob(Entity* mobAvatar) {
	vec3 openGLPosition = mobAvatar->getPosition();
	openGLPosition.y -= (float)mobAvatar->getScale().y / 2;
	vec2 position = Converter::fromOpenGLToMap(vec2(openGLPosition.x, openGLPosition.y));
	mobMap[(int)position.x][(int)position.y] = false;
}

void Map::nullMobMap() {
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			mobMap[i][j] = true;
		}
	}
}

void Map::updateMobMap() {
	nullMobMap();
	for (MobSpawner* spawner : *spawners) {
		for (Monster* mob : *spawner->getMobs()) {
			markMob(mob->getAvatar());
		}
	}
}

void Map::addItem(Item* item, float x, float y) {
	vec2 coords = Converter::fromMapToOpenGL(vec2(x, y));
	item->getDropped()->setPosition(vec3(coords.x, coords.y, y * 0.001f + 0.0015f));
	items.push_back(item);
}

list<GuiElement*> Map::getTitles(float posX, float posY, int horyzontalSide, int verticalSide) {
	list<GuiElement*> result = {};
	for (Item* item : items) {
		vec3 pos = item->getDropped()->getPosition();
		vec2 pos2D = Converter::fromOpenGLToMap(vec2(pos.x, pos.y));
		if (pos2D.x < posX + horyzontalSide && pos2D.x > posX - horyzontalSide && pos2D.y < posY + verticalSide && pos2D.y > posY - verticalSide) {
			item->getDropped()->update();
			for (GuiElement* gui : item->getDropped()->getTitle()->getIcons()) {
				result.push_back(gui);
			}
		}
	}
	return result;
}