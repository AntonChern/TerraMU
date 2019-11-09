#include "WayHandler.h"

void WayHandler::paveRoute() {
	Point* current = end;
	while (current != start) {
		wayAStar.push_front(current);
		if (current->getFrom()) {
			current = current->getFrom();
		} else {
			wayAStar.clear();
			return;
		}
	}
	wayAStar.push_front(current);
}

void WayHandler::nullAll() {
	deleteMap(mapWidth, mapHeight);

	wayAStar.clear();

	start = nullptr;
	end = nullptr;
}

queue<vec2>* WayHandler::buildWay(float startX, float startY, float endX, float endY, bool** map, int mapWidth, int mapHeight) {
	resultWay = new queue<vec2>();
	
	initMap(mapWidth, mapHeight);
	wayMap = map;
	WayHandler::mapWidth = mapWidth;
	WayHandler::mapHeight = mapHeight;

	aStar(startX, startY, endX, endY);
	paveRoute();
	if (!wayAStar.empty()) {
		straightenWay(startX, startY, endX, endY);
	}
	nullAll();

	return resultWay;
}

void WayHandler::aStar(float startX, float startY, float endX, float endY) {
	end = getPoint((int)endX, (int)endY);

	start = getPoint((int)startX, (int)startY);
	start->setG(0);
	start->setF(start->getG() + H(start));

	list<Point*> open = {};
	list<Point*> closed = {};

	open.push_back(start);

	while (!open.empty()) {
		Point* current = min_F(open);
		if (current == end) {
			return;
		}
		open.remove(current);
		closed.push_back(current);

		list<Point*> neighbours = { getPoint(current->getX() + 1, current->getY()),
								    getPoint(current->getX() - 1, current->getY()),
								    getPoint(current->getX(), current->getY() + 1),
								    getPoint(current->getX(), current->getY() - 1) };
		for (Point* neighbour : neighbours) {
			if (neighbour != nullptr && !contains(closed, neighbour)) {
				float temp_G = current->getG() + 1;
				if (!contains(open, neighbour) || temp_G < neighbour->getG()) {
					neighbour->setFrom(current);
					neighbour->setG(temp_G);
					neighbour->setF(neighbour->getG() + H(neighbour));
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
		if (cell->getF() < resultF) {
			resultF = cell->getF();
			result = cell;
		}
	}
	return result;
}

float WayHandler::H(Point* cell) {
	float widthSquare = (cell->getX() - end->getX()) * (cell->getX() - end->getX());
	float heightSquare = (cell->getY() - end->getY()) * (cell->getY() - end->getY());
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
}

void WayHandler::deleteMap(int width, int height) {
	for(int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			delete map[i][j];
		}
		delete[] map[i];
	}
	delete[] map;
}

void WayHandler::straightenWay(float startX, float startY, float endX, float endY) {
	vec2 start = vec2(startX, startY);

	list<Point*>::iterator iterator = wayAStar.begin();
	Point* curCell = *iterator;

	vec2 last = vec2(endX, endY);
	vec2 end = vec2(curCell->getX() + 0.5, curCell->getY() + 0.5);
	vec2 localWay = end - start;

	if (curCell == WayHandler::end) {
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
			end = curCell != WayHandler::end ? vec2(curCell->getX() + 0.5, curCell->getY() + 0.5) : last;
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
