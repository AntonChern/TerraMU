//#pragma once
//#include "InventoryGUI.h"
//#include "Entity.h"
//#include "Loader.h"
//#include "Renderer.h"
//
//class GUI : public Moveable {
//private:
//	InventoryGUI* inventory;
//	Entity* chest;
//	Entity* points;
//	Entity* bars;
//
//	void initInventory(Loader* loader, char const path[]);
//	void initChest(Loader* loader, char const path[]);
//	void initPoints(Loader* loader, char const path[]);
//	void initBars(Loader* loader, char const path[]);
//
//public:
//	GUI(Loader* loader, char const inventoryPath[], char const chestPath[], char const pointsPath[], char const barsPath[]);
//
//	void draw(Renderer* renderer);
//
//	void showInventory();
//	void hideInventory();
//
//	void showChest();
//	void hideChest();
//
//	void showPoints();
//	void hidePoints();
//
//	vec3 getPosition() { return position; };
//	float getRotationX() { return rotationX; };
//	float getRotationY() { return rotationY; };
//	float getRotationZ() { return rotationZ; };
//	vec3 getScale() { return scale; };
//
//	void setPosition(float x, float y, float z) { position = vec3(x, y, z); };
//	void setPosition(vec3 position) { this->position = position; };
//	void setScale(vec3 s) { scale = s; };
//	void setScale(float s) { scale = vec3(s); };
//	void setScale(float xScale, float yScale, float zScale) { scale = vec3(xScale, yScale, zScale); };
//	void setRotationX(float r) { rotationX = r; };
//	void setRotationY(float r) { rotationY = r; };
//	void setRotationZ(float r) { rotationZ = r; };
//
//	void increasePosition(float dx, float dy, float dz) { position += vec3(dx, dy, dz); };
//	void increasePosition(vec3 dv) { position += dv; };
//	void increaseScale(vec3 ds) { scale += ds; };
//	void increaseScale(float ds) { scale += vec3(ds); };
//	void increaseScale(float dxScale, float dyScale, float dzScale) { scale += vec3(dxScale, dyScale, dzScale); };
//	void increaseRotationX(float dr) { rotationX += dr; };
//	void increaseRotationY(float dr) { rotationY += dr; };
//	void increaseRotationZ(float dr) { rotationZ += dr; };
//
//};