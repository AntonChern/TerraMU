#pragma once
#include <list>
#include <iostream>
using namespace std;

class WayHandler {
private:
	class Point {
	public:
		Point(int x, int y) { this->x = x; this->y = y; };

		int x;
		int y;
		float G;
		float F;
		Point* from;
	};

	int mapLength;
	Point*** map;
	Point* end;
	Point* start;
	list<Point*> closed;
	list<Point*> open;

	Point* getPoint(int x, int y);
	Point* min_F(list<Point*> list);
	bool contains(list<Point*> list, Point* select);
	float H(Point* cell);
	void initMap(int length);
	void paveRoute(bool** map, int mapLength);
	void deleteMap();
public:
	WayHandler() { open = {}; closed = {}; };
	~WayHandler() { deleteMap(); };

	void buildWay(float startX, float startY, float finishX, float finishY, bool** map, int mapLength);
	void printMap(bool** map);
};

