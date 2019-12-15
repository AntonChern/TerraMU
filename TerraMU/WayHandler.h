#pragma once
#define GLM_FORCE_RADIANS
#include <list>
#include <queue>
#include <stack>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <cmath>
#include <iostream>
using namespace glm;
using namespace std;

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

	static float radius;
	static bool** wayMap;
	static Point*** map;
	static Point* end;
	static Point* start;
	static list<Point*> wayAStar;
	static list<vec2>* resultWay;

	static Point* getPoint(int x, int y);
	static Point* min_F(list<Point*> list);
	static bool contains(list<Point*> list, Point* select);
	static float H(Point* origin, Point* whither);
	static void initMap();
	static void initAll(float visibilityRadius, vec2 origin, vec2 whither);
	//static void deleteMap();
	static void nullMap();
	static void paveRoute();

	static void aStar();
	static void straightenWay(vec2 origin, vec2 whither);
	static bool existsWay(vec2 start, vec2 way);
	static void nullAll();
	static int sgn(float value);

	static bool isInRadius(Point* cell);
	static void nullOddCells();

public:
	WayHandler();
	~WayHandler();
	static void initialize();
	static void deinitialize();

	static list<vec2>* buildWay(float visibilityRadius, vec2 origin, vec2 whither);
	static bool existsPath(float visibilityRadius, vec2 origin, vec2 whither);
	static vec2 getOptimalEnd(float visibilityRadius, vec2 origin, vec2 whither);
	static bool isWalkable(list<vec2>* path, vec2 origin, vec2 initial);
};

