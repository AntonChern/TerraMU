#include "WayHandler.h"
#include <cmath>
using namespace std;

//void WayHandler::printMap() {
//	cout << "+";
//	for (int i = 0; i < mapWidth; i++)
//	{
//		cout << "-";
//	}
//	cout << "+" << endl;
//	for (int j = 0; j < mapHeight; j++) {
//		cout << "|";
//		for (int i = 0; i < mapWidth; i++) {
//			if (auxiliaryMap[i][j]) {
//				cout << ".";
//			}
//			else {
//				if (wayMap[i][j]) {
//					cout << " ";
//				} else {
//					cout << "#";
//				}
//			}
//		}
//		cout << "|" << endl;
//	}
//	cout << "+";
//	for (int i = 0; i < mapWidth; i++)
//	{
//		cout << "-";
//	}
//	cout << "+" << endl;
//}

void WayHandler::paveRoute() {
	Point* current = end;
	while (current != start) {
		wayAStar.push_front(current);
		current = current->from;
	}
	wayAStar.push_front(current);

	for (Point* cell : wayAStar) {
		auxiliaryMap[cell->x][cell->y] = true;
	}
}

void WayHandler::nullAll() {
	deleteMap(mapWidth, mapHeight);

	open.clear();
	closed.clear();
	wayAStar.clear();

	start = nullptr;
	end = nullptr;
}

queue<vec2>* WayHandler::buildWay(float startX, float startY, float endX, float endY, bool** map, int mapWidth, int mapHeight) {
	resultWay = new queue<vec2>();
	
	initMap(mapWidth, mapHeight);
	wayMap = map;
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;

	aStar(startX, startY, endX, endY);
	paveRoute();
	straightenWay(startX, startY, endX, endY);
	nullAll();

	return resultWay;
}

void WayHandler::aStar(float startX, float startY, float endX, float endY) {
	end = getPoint((int)endX, (int)endY);

	start = getPoint((int)startX, (int)startY);
	start->G = 0;
	start->F = start->G + H(start);

	open.push_back(start);

	while (!open.empty()) {
		Point* current = min_F(open);
		if (current == end) {
			return;
		}
		open.remove(current);
		closed.push_back(current);

		list<Point*> neighbours = { getPoint(current->x + 1, current->y),
								    getPoint(current->x - 1, current->y),
								    getPoint(current->x, current->y + 1),
								    getPoint(current->x, current->y - 1) };
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
	if ((x >= 0 && x < mapWidth) && (y >= 0 && y < mapHeight) && wayMap[x][y]) {
		return map[x][y];
	}
	return nullptr;
}

WayHandler::Point* WayHandler::min_F(list<Point*> list) {
	float resultF = INFINITY;
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
	return std::sqrt(widthSquare + heightSquare);
}

void WayHandler::initMap(int width, int height) {
	map = new Point** [width] {nullptr};
	for (int i = 0; i < width; i++) {
		map[i] = new Point* [height] {nullptr};
		for (int j = 0; j < height; j++) {
			map[i][j] = new Point(i, j);
		}
	}

	auxiliaryMap = new bool* [width] {nullptr};
	for (int i = 0; i < width; i++) {
		auxiliaryMap[i] = new bool[height] {false};
	}
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			auxiliaryMap[i][j] = false;
		}
	}
}

void WayHandler::deleteMap(int width, int height) {
	for(int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			delete map[i][j];
		}
		delete[] map[i];
	}
	delete[] map;

	for (int i = 0; i < width; i++) {
		delete[] auxiliaryMap[i];
	}
	delete[] auxiliaryMap;
}

void WayHandler::straightenWay(float startX, float startY, float endX, float endY) {
	vec2 start = vec2(startX, startY);

	list<Point*>::iterator iterator = wayAStar.begin();
	Point* curCell = *iterator;

	vec2 last = vec2(endX, endY);
	vec2 end = vec2(curCell->x + 0.5, curCell->y + 0.5);
	vec2 localWay = end - start;

	if (curCell == this->end) {
		resultWay->push(last - start);
		return;
	}

	while (end != last) {
		stack<vec2> existingWays = {};
		list<Point*>::iterator bufferedIterator;
		while (end != last) {
			if (existsWay(start, localWay)) {
				existingWays.push(localWay);
				bufferedIterator = iterator;
			}
			iterator++;
			curCell = *iterator;
			end = curCell != this->end ? vec2(curCell->x + 0.5, curCell->y + 0.5) : last;
			localWay = end - start;
		}
		if (existsWay(start, localWay)) {
			existingWays.push(localWay);
		}
		vec2 result = existingWays.top();
		start = end = start + result;
		localWay = end - start;
		resultWay->push(result);
		iterator = bufferedIterator;
	}
}

bool WayHandler::existsWay(vec2 start, vec2 way) {
	int step = sgn(way.x);
	int divisions = ((int)(start.x + way.x) - (int)start.x) * step;
	float divisionX = (int)start.x - start.x + (1 + step) / 2;
	for (int i = 0; i < divisions; i++) {
		vec2 helper = vec2(divisionX, divisionX * way.y / way.x);
		vec2 selectPoint = start + helper;
		int xIndex = (int)selectPoint.x;
		int yIndex = (int)selectPoint.y;
		if (!wayMap[xIndex][yIndex] || (yIndex == selectPoint.y && (yIndex > 0 && yIndex <= mapHeight) && !wayMap[xIndex][yIndex - 1])) {
			return false;
		}
		divisionX += step;
	}

	step = sgn(way.y);
	divisions = ((int)(start.y + way.y) - (int)start.y) * step;
	float divisionY = (int)start.y - start.y + (1 + step) / 2;
	for (int i = 0; i < divisions; i++) {
		vec2 helper = vec2(divisionY * way.x / way.y, divisionY);
		vec2 selectPoint = start + helper;
		int xIndex = (int)selectPoint.x;
		int yIndex = (int)selectPoint.y + (sgn(way.x * way.y) - 1) / 2;
		if (!wayMap[xIndex][yIndex] || (xIndex == selectPoint.x && (xIndex > 0 && xIndex <= mapWidth) && !wayMap[xIndex - 1][yIndex])) {
			return false;
		}
		divisionY += step;
	}
	return true;
}

int WayHandler::sgn(float value) {
	return value >= 0 ? 1 : -1;
}

//void WayHandler::printResult() {
//	while (!resultWay->empty()) {
//		vec2 current = resultWay->front();
//		resultWay->pop();
//		cout << current.x << ":" << current.y << endl;
//	}
//}