#include "Map.h"
#include <fstream> // beg delete
#include <iostream>
#include <sstream>
using namespace std; // end delete

Map::Map(const char* sourcePath, vec3 position, float rotationX, float rotationY, float rotationZ, float scale) {

	columns = 255;
	rows = 255;

	//MEMORY
	base = new Tile*[columns];
	for (int i = 0; i < columns; i++) {
		base[i] = new Tile[rows];
	}
	hat = new Tile * [columns];
	for (int i = 0; i < columns; i++) {
		hat[i] = new Tile[rows];
	}
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			hat[i][j] = EMPTY;
		}
	}

	char currSymb = 0;
	ifstream fin3(sourcePath);
	int i = 0;
	while (!fin3.eof()) {
		int number = 0;
		fin3.get(currSymb);
		number = currSymb - '0';
		if (number < 0 || number > 8) {
			continue;
		}

		Tile currTile = EMPTY;
		base[i % columns][(i - i % columns) / columns] = GRASS_0;
		switch (number) {
		case 1:
			base[i % columns][(i - i % columns) / columns] = GRASS_0;
			break;
		case 2:
			base[i % columns][(i - i % columns) / columns] = GRASS_1;
			break;
		case 3:
			base[i % columns][(i - i % columns) / columns] = GRASS_2;
			break;
		case 4:
			base[i % columns][(i - i % columns) / columns] = STONE_0;
			break;
		case 5:
			base[i % columns][(i - i % columns) / columns] = STONE_1;
			break;
		case 6:
			base[i % columns][(i - i % columns) / columns] = STONE_2;
			break;
		case 7:
			base[i % columns][(i - i % columns) / columns] = STONE_3;
			break;
		default:
			//cout << " " << endl;
			base[i % columns][(i - i % columns) / columns] = STONE_4;
			break;
		}

		//base[i % columns][(i - i % columns) / columns] = currTile;

		i++;
	}
	fin3.close();

	this->position = position;
	this->rotationX = rotationX;
	this->rotationY = rotationY;
	this->rotationZ = rotationZ;
	this->scale = vec3(scale);

	//Map::Map(columns, rows, base, hat, position, rotationX, rotationY, rotationZ, scale);
}

void Map::drawLayer(Tile** layer, float offset, Renderer* renderer, Loader* loader, StreamShader* shader,
	float posX, float posY, int horyzontalSide, int verticalSide) {

	horyzontalSide += (horyzontalSide + 1) % 2;
	verticalSide += (verticalSide + 1) % 2;

	int centerX = (int)(posX);
	int centerY = (int)(posY);

	int startX = centerX - horyzontalSide / 2;
	int startY = centerY - verticalSide / 2;

	int endX = centerX + horyzontalSide / 2;
	int endY = centerY + verticalSide / 2;

	for (int j = max(0, startY); j < rows && j <= endY; j++) {
		for (int i = max(0, startX); i < columns && i <= endX; i++) {
			Tile currTile = layer[i][j];

			if (currTile == EMPTY) {
				continue;
			}

			MapObject* currMapObject = nullptr;
			try {
				currMapObject = mapObjects.at(currTile);
			}
			catch (const out_of_range & exc) {
				cerr << "Out of Range error: " << exc.what() << endl;
				cerr << "Map::mapObjects doesn't contain this Tile: " << currTile << endl;
				continue;
			}

			vec3 currPosition = vec3(position.x + scale.x * ((float)(2 * i + 1) / columns - 1),
				position.y + scale.y * ((-2 * (j + 1) + (float)currMapObject->getHeight() / cellHeight) / rows + 1),
				offset * (j + 1));

			vec3 currScale = vec3(2 * this->scale.x * currMapObject->getWidth() / (columns * cellWidth),
				2 * this->scale.y * currMapObject->getHeight() / (rows * cellHeight), 1.0f);

			Entity* currEntity = nullptr;
			try {
				currEntity = entities->at(currTile);
				currEntity->setPosition(currPosition);
				currEntity->setRotationX(this->rotationX);
				currEntity->setRotationY(this->rotationY);
				currEntity->setRotationZ(this->rotationZ);
				currEntity->setScale(currScale);
			}
			catch (const out_of_range & exc) {
				currEntity = EntityBuilder::createEntity(loader, currMapObject->getTexturePath(),
					currPosition, this->rotationX, this->rotationY, this->rotationZ, currScale);

				//currEntity->increaseScale(2 * this->scale / columns);

				entities->insert(pair<Tile, Entity*>(currTile, currEntity));
			}

			if (currMapObject->getIsVisible()) {
				renderer->render(currEntity, shader);
			}
		}
	}
}

void Map::drawRectangleArea(Renderer *renderer, Loader* loader, StreamShader *shader,
	float posX, float posY, int horyzontalSide, int verticalSide) {
	drawLayer(base, 0.0f, renderer, loader, shader, posX, posY, horyzontalSide, verticalSide);
	drawLayer(hat, 0.001f, renderer, loader, shader, posX, posY, horyzontalSide, verticalSide);
}

void Map::interact(float x, float y) {
	int coordX = (int)(x + 0.5f);
	int coordY = (int)(y + 0.5f);

	for (int i = rows - 1; i >= coordY; i--) {

	}

}