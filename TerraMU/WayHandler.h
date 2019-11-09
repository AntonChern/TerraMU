#pragma once
#include <list>
#include <queue>
#include <stack>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <cmath>
#include <iostream>
using namespace std;
using namespace glm;

class WayHandler {
private:
	class Point {
	private:
		int x;
		int y;
		float G;
		float F;
		Point* from;
	public:
		Point(int x, int y) { Point::x = x; Point::y = y; };

		int getX() { return Point::x; };
		int getY() { return Point::y; };
		float getG() { return Point::G; };
		float getF() { return Point::F; };
		Point* getFrom() { return Point::from; };

		void setX(int x) { Point::x = x; };
		void setY(int y) { Point::y = y; };
		void setG(float G) { Point::G = G; };
		void setF(float F) { Point::F = F; };
		void setFrom(Point* from) { Point::from = from; };
	};

	static int mapWidth;
	static int mapHeight;
	static bool** wayMap;
	static Point*** map;
	static Point* end;
	static Point* start;
	static list<Point*> wayAStar;
	static queue<vec2>* resultWay;

	static Point* getPoint(int x, int y);
	static Point* min_F(list<Point*> list);
	static bool contains(list<Point*> list, Point* select);
	static float H(Point* cell);
	static void initMap(int width, int height);
	static void deleteMap(int width, int height);
	static void paveRoute();

	static void aStar(float startX, float startY, float finishX, float finishY);
	static void straightenWay(float startX, float startY, float endX, float endY);
	static bool existsWay(vec2 start, vec2 way);
	static void nullAll();
	static int sgn(float value);
public:
	WayHandler() {};
	~WayHandler() { deleteMap(mapWidth, mapHeight); };

	static queue<vec2>* buildWay(float startX, float startY, float finishX, float finishY, bool** map, int mapWidth, int mapHeight);
};

