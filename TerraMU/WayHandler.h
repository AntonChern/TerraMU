#pragma once
#include <list>
#include <queue>
#include <stack>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <iostream>
using namespace std;
using namespace glm;


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
	bool** wayMap;
	bool** auxiliaryMap;
	Point*** map;
	Point* end;
	Point* start;
	list<Point*> closed;
	list<Point*> open;
	list<Point*> wayAStar;
	queue<vec2>* resultWay;

	Point* getPoint(int x, int y);
	Point* min_F(list<Point*> list);
	bool contains(list<Point*> list, Point* select);
	float H(Point* cell);
	void initMap(int length);
	void deleteMap(int length);
	void paveRoute();

	void aStar(float startX, float startY, float finishX, float finishY);
	void straightenWay(float startX, float startY, float endX, float endY);
	bool existsWay(vec2 start, vec2 way);
	void nullAll(int mapLength);
	int sgn(float value);
public:
	WayHandler() { open = {}; closed = {}; wayAStar = {}; };
	~WayHandler() { deleteMap(mapLength); };

	queue<vec2>* buildWay(float startX, float startY, float finishX, float finishY, bool** map, int mapLength);
	void printMap();
	void printResult();
};

