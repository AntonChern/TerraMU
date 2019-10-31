#include "Camera.h"
#include "Display.h"

Camera::Camera(/*GUI* gui*/) : /*gui(gui),*/ position(vec3(0.0f, 0.0f, 0.0f)), roll(0.0f), yaw(0.0f), pitch(0.0f) {
	/*gui->setPosition(position);
	gui->setRotationX(pitch);
	gui->setRotationX(pitch);
	gui->setRotationX(pitch);*/
	//float aspect = (float)Display::getWidth() / (float)Display::getHeight();
	//gui->setScale(vec3(2.0f * aspect, 2.0f, 1.0f));
};