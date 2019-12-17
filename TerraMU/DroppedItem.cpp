#include "DroppedItem.h"
#include "FramedLabel.h"
#include "EntityFactory.h"
#include "Converter.h"

DroppedItem::DroppedItem(string texturePath, string title, vec3 position, float rotationX, float rotationY, float rotationZ, vec3 scale) :
	Moveable(position, rotationX, rotationY, rotationZ, scale) {
	this->model = EntityFactory::createEntity(texturePath.c_str(), position, rotationX, rotationY, rotationZ, scale);

	vec2 position2D = vec2(position.x, position.y + scale.y);
	position2D = Converter::fromOpenGLToGui(position2D);
	position = vec3(position2D.x, position2D.y, 0.0f);

	this->title = new FramedLabel(title, position, 0.0f, 0.0f, 0.0f, scale.x * scaleCoeff);
}

DroppedItem::~DroppedItem() {
	delete this->title;
	EntityFactory::cleanEntities({ model });
}

void DroppedItem::setPosition(vec3 position) {
	this->position = position;
	model->setPosition(position);

	update();
}

void DroppedItem::setScale(vec3 s) {
	this->scale = s;
	model->setScale(s);
	title->setScale(s * scaleCoeff);
}

void DroppedItem::setRotationX(float r) {
	this->rotationX = rotationX;
	model->setRotationX(r);
}

void DroppedItem::setRotationY(float r) {
	this->rotationY = rotationY;
	model->setRotationY(r);
}

void DroppedItem::setRotationZ(float r) {
	this->rotationZ = rotationZ;
	model->setRotationZ(r);
}

void DroppedItem::update() {
	vec2 position2D = vec2(position.x, position.y + scale.y / 2);
	position2D = Converter::fromOpenGLToGui(position2D);

	title->setPosition(vec3(position2D.x, position2D.y, 0.0f));
}
