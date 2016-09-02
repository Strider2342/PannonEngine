#include "Object.h"

Object::Object()
{
	transform = new Transform();
	script = new Script();
}

Object::~Object()
{
	delete transform;
	delete script;

	transform = nullptr;
	script = nullptr;
}

Transform * Object::GetTransform()
{
	return transform;
}

Script * Object::GetScript()
{
	return script;
}

void Object::SetTransform(Transform * transform)
{
	this->transform = transform;
}

void Object::SetScript(Script * script)
{
	this->script = script;
}
