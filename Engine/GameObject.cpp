#include "GameObject.h"

GameObject::GameObject()
{ }

GameObject::~GameObject()
{ }

void GameObject::Start()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Start();
	}
}
void GameObject::PreUpdate()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->PreUpdate();
	}
}
void GameObject::Update(GameTime gameTime)
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Update(gameTime);
	}
}
void GameObject::PostUpdate()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->PostUpdate();
	}
}
void GameObject::Render()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Render();
	}
}

void GameObject::OnCollision()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->OnCollision();
	}
}
void GameObject::OnCollisionEnter()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->OnCollisionEnter();
	}
}
void GameObject::OnCollisionStay()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->OnCollisionStay();
	}
}
void GameObject::OnCollisionExit()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->OnCollisionExit();
	}
}

Transform* GameObject::GetTransform()
{
	return transform;
}
std::string GameObject::GetName()
{
	return name;
}

bool GameObject::IsEmpty()
{
	return isEmpty;
}

void GameObject::SetName(std::string name)
{
	this->name = name;
}
