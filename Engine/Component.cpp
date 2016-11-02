#include "Component.h"

Component::Component()
{ }
Component::~Component()
{ }

void Component::Start()
{ }
void Component::PreUpdate()
{ }
void Component::Update(GameTime gameTime, Input input)
{ }
void Component::PostUpdate()
{
}
void Component::Render()
{ }
void Component::PostRender()
{
}

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