#include "Maths.h"

mat4 Maths::createTransformMatrix(vec3 position, float rotX, float rotY, float rotZ, float scal) {
	mat4 transform(1.0f);
	transform = translate(transform, position);
	transform = rotate(transform, radians(rotX), vec3(1.0f, 0.0f, 0.0f));
	transform = rotate(transform, radians(rotY), vec3(0.0f, 1.0f, 0.0f));
	transform = rotate(transform, radians(rotZ), vec3(0.0f, 0.0f, 1.0f));
	transform = scale(transform, vec3(scal));
	return transform;
}

mat4 Maths::createViewMatrix(Camera *camera) {
	mat4 view(1.0f);
	view = rotate(view, radians(camera->getPitch()), vec3(1.0f, 0.0f, 0.0f));
	view = rotate(view, radians(camera->getYaw()), vec3(0.0f, 1.0f, 0.0f));
	view = rotate(view, radians(camera->getRoll()), vec3(0.0f, 0.0f, 1.0f));
	view = translate(view, -camera->getPosition());
	return view;
}