#include "Component.h"

Component::Component()
{ }

Component::~Component()
{ }

void Component::Start()
{ }

void Component::Update(GameTime gameTime)
{ }

void Component::Render()
{ }

void Component::SetGameObject(GameObject * gameObject)
{
	this->gameObject = gameObject;
}
