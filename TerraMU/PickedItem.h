#pragma once
class Picture;
#include <string>
using namespace std;

class PickedItem {
private:
	Picture* icon;

public:
	PickedItem(string texturePath);
	~PickedItem();

	Picture* getIcon() { return icon; };

};