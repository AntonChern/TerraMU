#include "WayHandler.h"
#include <list>
#include <iostream>
#include <cmath>
using namespace std;

const float maxValue = 99999;

void WayHandler::printMap(bool** map) {
	cout << "+";
	for (int i = 0; i < mapLength; i++)
	{
		cout << "-";
	}
	cout << "+" << endl;
	for (int j = 0; j < mapLength; j++) {
		cout << "|";
		for (int i = 0; i < mapLength; i++) {
			if (map[i][j]) {
				cout << "#";
			}
			else {
				cout << " ";
			}
		}
		cout << "|" << endl;
	}
	cout << "+";
	for (int i = 0; i < mapLength; i++)
	{
		cout << "-";
	}
	cout << "+" << endl;
}

void WayHandler::paveRoute(bool** map, int mapLength) {
	list<Point*> way = {};
	Point* current = end;
	while (current != start) {
		way.push_back(current);
		current = current->from;
	}
	way.push_back(current);

	for (int i = 0; i < mapLength; i++) {
		for (int j = 0; j < mapLength; j++) {
			if (contains(way, this->map[i][j])) {
				map[i][j] = true;
			}
		}
	}
}

void WayHandler::buildWay(float startX, float startY, float endX, float endY, bool** map, int mapLength) {
	initMap(mapLength);
	this->mapLength = mapLength;

	end = getPoint((int)(endX + 0.5), (int)(endY + 0.5));

	start = getPoint((int)(startX + 0.5), (int)(startY + 0.5));
	start->G = 0;
	start->F = start->G + H(start);

	open.push_back(start);

	while (!open.empty()) {
		Point* current = min_F(open);
		if (current == end) {
			paveRoute(map, mapLength);
			return;
		}
		open.remove(current);
		closed.push_back(current);
		
		list<Point*> neighbours = {getPoint(current->x + 1, current->y),
								   getPoint(current->x - 1, current->y),
								   getPoint(current->x, current->y + 1),
								   getPoint(current->x, current->y - 1)};
		for (Point* neighbour : neighbours) {
			if (neighbour != nullptr && !contains(closed, neighbour)) {
				float temp_G = current->G + 1;
				if (!contains(open, neighbour) || temp_G < neighbour->G) {
					neighbour->from = current;
					neighbour->G = temp_G;
					neighbour->F = neighbour->G + H(neighbour);
				}
				if (!contains(open, neighbour)) {
					open.push_back(neighbour);
				}
			}
		}
	}
}

bool WayHandler::contains(list<Point*> list, Point* select) {
	for (Point* cell : list) {
		if (select == cell) {
			return true;
		}
	}
	return false;
}

WayHandler::Point* WayHandler::getPoint(int x, int y) {
	if ((x >= 0 && x < mapLength) && (y >= 0 && y < mapLength)) {
		return map[x][y];
	}
	return nullptr;
}

WayHandler::Point* WayHandler::min_F(list<Point*> list) {
	float resultF = maxValue;
	Point* result = nullptr;
	for (Point* cell : list) {
		if (cell->F < resultF) {
			resultF = cell->F;
			result = cell;
		}
	}
	return result;
}

float WayHandler::H(Point* cell) {
	float widthSquare = (cell->x - end->x) * (cell->x - end->x);
	float heightSquare = (cell->y - end->y) * (cell->y - end->y);
	return sqrt(widthSquare + heightSquare);
}

void WayHandler::initMap(int length) {
	map = new Point** [length] {nullptr};
	for (int i = 0; i < length; i++) {
		map[i] = new Point* [length] {nullptr};
		for (int j = 0; j < length; j++) {
			map[i][j] = new Point(i, j);
		}
	}
}

void WayHandler::deleteMap() {
	for (int i = 0; i < mapLength; i++) {
		for (int j = 0; j < mapLength; j++) {
			delete map[i][j];
		}
		delete[] map[i];
	}
	delete[] map;
}