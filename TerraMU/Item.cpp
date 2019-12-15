#include "Item.h"
#include "DroppedItem.h"
#include "PickedItem.h"
#include "GoAction.h"
#include "PickUpItemAction.h"
#include "Converter.h"
#include "GameController.h"

Item::Item(string texturePath, string name) {
	dropped = new DroppedItem(texturePath, name, vec3(0.0f), 0.0f, 0.0f, 0.0f, GameController::WORLD_SCALE);
	picked = new PickedItem(texturePath);
}

Item::~Item() {
	delete dropped;
	delete picked;
}

void Item::interact() {
	vec2 pos = Converter::fromOpenGLToMap(vec2(dropped->getPosition().x, dropped->getPosition().y));
	GameController::setActions({new GoAction(pos.x, pos.y), new PickUpItemAction(this)});
}
