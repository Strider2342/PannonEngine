#include "GameObject.h"

GameObject::GameObject()
{ }

GameObject::~GameObject()
{ }

void GameObject::Init(ID3D11Device *dev, ID3D11DeviceContext *devcon)
{
	this->dev = dev;
	this->devcon = devcon;
}

void GameObject::Start()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Start();
	}
}
void GameObject::Update(GameTime gameTime)
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Update(gameTime);
	}
}
void GameObject::Render()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Render();
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
