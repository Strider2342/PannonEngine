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

void Component::OnCollision()
{ }
void Component::OnCollisionEnter()
{ }
void Component::OnCollisionStay()
{ }
void Component::OnCollisionExit()
{ }

void Component::SetGameObject(GameObject *gameObject)
{
	this->gameObject = gameObject;
}
