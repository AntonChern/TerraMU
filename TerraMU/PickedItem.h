#pragma once
#include "Picture.h"

class PickedItem {
private:
	Picture* icon;

public:
	PickedItem(string texturePath);
	~PickedItem();

	Picture* getIcon() { return icon; };

};