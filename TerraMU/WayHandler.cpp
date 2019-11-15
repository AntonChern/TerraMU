#include "WayHandler.h"
#include "GameController.h"

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
	deleteMap();

	wayAStar.clear();

	start = nullptr;
	end = nullptr;
}

bool WayHandler::isInRadius(Point* cell) {
	return H(cell, start) <= radius;
}

void WayHandler::nullOddCells() {
	for (int i = 0; i < GameController::getMap()->getColumns(); i++) {
		for (int j = 0; j < GameController::getMap()->getRows(); j++) {
			Point* cell = getPoint(i, j);
			if (cell && !isInRadius(cell)) {
				wayMap[i][j] = false;
			}
		}
	}
}

void WayHandler::initAll(float visibilityRadius, vec2 origin, vec2 whither) {
	WayHandler::radius = visibilityRadius;

	initMap();
	wayMap[(int)origin.x][(int)origin.y] = GameController::getMap()->getReachMap()[(int)origin.x][(int)origin.y];

	start = WayHandler::map[(int)origin.x][(int)origin.y];
	end = WayHandler::map[(int)whither.x][(int)whither.y];

	nullOddCells();
}

bool WayHandler::existsPath(float visibilityRadius, vec2 origin, vec2 whither) {
	initAll(visibilityRadius, origin, whither);

	start->setG(0);
	start->setF(WayHandler::start->getG() + H(WayHandler::start, end));

	list<Point*> open = { start };
	list<Point*> closed = {};

	while (!open.empty()) {
		Point* current = min_F(open);
		if (current == end) {
			nullAll();
			return true;
		}
		open.remove(current);
		closed.push_back(current);

		list<Point*> neighbours = { getPoint(current->getX() + 1, current->getY()),
									getPoint(current->getX() - 1, current->getY()),
									getPoint(current->getX(), current->getY() + 1),
									getPoint(current->getX(), current->getY() - 1) };
		for (Point* neighbour : neighbours) {
			if (neighbour && !contains(closed, neighbour)) {
				float temp_G = current->getG() + 1;
				if (!contains(open, neighbour) || temp_G < neighbour->getG()) {
					neighbour->setG(temp_G);
					neighbour->setF(neighbour->getG() + H(neighbour, end));
				}
				if (!contains(open, neighbour)) {
					open.push_back(neighbour);
				}
			}
		}
	}

	nullAll();
	return false;
}

vec2 WayHandler::getOptimalEnd(float visibilityRadius, vec2 origin, vec2 whither) {
	initAll(visibilityRadius, origin, whither);

	list<Point*> closed = {};
	list<Point*> open = { start };

	Point* result = start;
	float resultH = H(result, end);

	while (!open.empty()) {
		Point* current = open.front();
		open.remove(current);
		closed.push_back(current);

		list<Point*> neighbours = { getPoint(current->getX() + 1, current->getY()),
									getPoint(current->getX() - 1, current->getY()),
									getPoint(current->getX(), current->getY() + 1),
									getPoint(current->getX(), current->getY() - 1) };
		for (Point* neighbour : neighbours) {
			if (neighbour && !contains(closed, neighbour)) {
				open.push_back(neighbour);
				if (H(neighbour, end) < resultH) {
					resultH = H(neighbour, end);
					result = neighbour;
				}
			}
		}
	}

	vec2 coordResult = vec2(result->getX() + 0.5f, result->getY() + 0.5f);
	nullAll();
	return coordResult;
}

bool WayHandler::isWalkable(list<vec2>* path, vec2 origin, vec2 initial) {
	if (!path) {
		return false;
	}
	initMap();

	list<vec2>::iterator iterator = path->begin();
	vec2 localWay = *iterator - origin + initial;
	vec2 start = origin;
	while (iterator != path->end()) {
		if (!existsWay(start, localWay)) {
			nullAll();
			return false;
		}
		start += localWay;
		localWay = *++iterator;
	}
	bool result = existsWay(start, localWay);
	nullAll();
	return result;
}

list<vec2>* WayHandler::buildWay(float visibilityRadius, vec2 origin, vec2 whither) {
	resultWay = new list<vec2>();
	initAll(visibilityRadius, origin, whither);

	aStar();
	paveRoute();

	if (!wayAStar.empty()) {
		straightenWay(origin, whither);
	}

	nullAll();
	return resultWay;
}

void WayHandler::aStar() {
	start->setG(0);
	start->setF(start->getG() + H(start, end));

	list<Point*> open = { start };
	list<Point*> closed = {};

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
			if (neighbour && !contains(closed, neighbour)) {
				float temp_G = current->getG() + 1;
				if (!contains(open, neighbour) || temp_G < neighbour->getG()) {
					neighbour->setFrom(current);
					neighbour->setG(temp_G);
					neighbour->setF(neighbour->getG() + H(neighbour, end));
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
	if ((x >= 0 && x < GameController::getMap()->getColumns()) && (y >= 0 && y < GameController::getMap()->getRows()) && wayMap[x][y]) {
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

float WayHandler::H(Point* origin, Point* whither) {
	float widthSquare = (origin->getX() - whither->getX()) * (origin->getX() - whither->getX());
	float heightSquare = (origin->getY() - whither->getY()) * (origin->getY() - whither->getY());
	return std::sqrt(widthSquare + heightSquare);
}

void WayHandler::initMap() {
	map = new Point** [GameController::getMap()->getColumns()] {};
	for (int i = 0; i < GameController::getMap()->getColumns(); i++) {
		map[i] = new Point* [GameController::getMap()->getRows()] {};
		for (int j = 0; j < GameController::getMap()->getRows(); j++) {
			map[i][j] = new Point(i, j);
		}
	}

	wayMap = new bool* [GameController::getMap()->getColumns()];
	for (int i = 0; i < GameController::getMap()->getColumns(); i++) {
		wayMap[i] = new bool[GameController::getMap()->getRows()];
		for (int j = 0; j < GameController::getMap()->getRows(); j++) {
			wayMap[i][j] = GameController::getMap()->getReachMap()[i][j] && GameController::getMap()->getMobMap()[i][j];
		}
	}
}

void WayHandler::deleteMap() {
	for(int i = 0; i < GameController::getMap()->getColumns(); i++) {
		for (int j = 0; j < GameController::getMap()->getRows(); j++) {
			delete map[i][j];
		}
		delete[] map[i];
	}
	delete[] map;

	for (int i = 0; i < GameController::getMap()->getColumns(); i++) {
		delete[] wayMap[i];
	}
	delete[] wayMap;
}

void WayHandler::straightenWay(vec2 origin, vec2 whither) {
	vec2 start = vec2(origin.x, origin.y);

	list<Point*>::iterator iterator = wayAStar.begin();
	Point* curCell = *iterator;

	vec2 last = vec2(whither.x, whither.y);
	vec2 end = vec2(curCell->getX() + 0.5, curCell->getY() + 0.5);
	vec2 localWay = end - start;

	if (curCell == WayHandler::end) {
		if (last - start != vec2(0.0f, 0.0f)) {
			resultWay->push_back(last - start);
		}
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
		if (result != vec2(0.0f, 0.0f)) {
			resultWay->push_back(result);
		}
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
		if (!wayMap[xIndex][yIndex] || (yIndex == selectPoint.y && (yIndex > 0 && yIndex <= GameController::getMap()->getRows()) && !wayMap[xIndex][yIndex - 1])) {
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
		if (!wayMap[xIndex][yIndex] || (xIndex == selectPoint.x && (xIndex > 0 && xIndex <= GameController::getMap()->getColumns()) && !wayMap[xIndex - 1][yIndex])) {
			return false;
		}
		divisionY += step;
	}
	return true;
}

int WayHandler::sgn(float value) {
	return value >= 0 ? 1 : -1;
}
