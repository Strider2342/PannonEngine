#include "Object.h"

Object::Object()
{
	transform = new Transform();
}

Object::~Object()
{
	delete transform;

	transform = nullptr;
}

Transform * Object::GetTransform()
{
	return transform;
}

void Object::SetTransform(Transform * transform)
{
	this->transform = transform;
}