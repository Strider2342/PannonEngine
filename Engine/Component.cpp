#include "Component.h"

Component::Component()
{ }

Component::~Component()
{ }

void Component::Start()
{ }

void Component::Update()
{ }

void Component::Render()
{ }

void Component::SetGameObject(GameObject * gameObject)
{
	this->gameObject = gameObject;
}
