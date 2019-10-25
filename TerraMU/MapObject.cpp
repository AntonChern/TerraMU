#include "MapObject.h"

Action MapObject::interact() {
	if (isReachable) {
		return GO;
	}

	return NONE;
}