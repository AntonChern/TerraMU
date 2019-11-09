#include "Map.h"
#include "Tile.h"
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

	for (int j = 0; j < rows; j++) {
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
	}
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
}

void Map::processLayer(Tile** layer, float offset, list<Entity*> &entities, float posX, float posY, int horyzontalSide, int verticalSide) {
	horyzontalSide += (horyzontalSide + 1) % 2;
	verticalSide += (verticalSide + 1) % 2;

	int startX = (int)(posX) - horyzontalSide / 2;
	int startY = (int)(posY) - verticalSide / 2;

	int endX = (int)(posX) + horyzontalSide / 2;
	int endY = (int)(posY) + verticalSide / 2;

	for (int j = std::max(0, startY); j < rows && j <= endY; j++) {
		for (int i = std::max(0, startX); i < columns && i <= endX; i++) {
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
				offset * (j + 1) + offset * i / (2 * columns));

			vec3 currScale = vec3(this->scale.x * currMapObject->getWidth() / (columns * cellWidth),
				this->scale.y * currMapObject->getHeight() / (rows * cellHeight), 1.0f);

			Entity* currEntity = EntityFactory::createEntity(currMapObject->getTexturePath(),
				currPosition, this->rotationX, this->rotationY, this->rotationZ, currScale);

			entities.push_back(currEntity);
		}
	}
}

list<Entity*> Map::getRectangleArea(float posX, float posY, int horyzontalSide, int verticalSide) {
	list<Entity*> entities;
	processLayer(base, 0.0f, entities, posX, posY, horyzontalSide, verticalSide);
	processLayer(hat, 0.001f, entities, posX, posY, horyzontalSide, verticalSide);
	return entities;
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

bool** Map::getReachMap() {
	return reachMap;
}