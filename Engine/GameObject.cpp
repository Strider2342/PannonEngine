#include "GameObject.h"

GameObject::GameObject()
{
	AddComponent<Transform>();
}

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
void GameObject::Update(GameTime gameTime, Input input)
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Update(gameTime, input);
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
void GameObject::PostRender()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->PostRender();
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
	return GetComponent<Transform>();
}
std::string GameObject::GetName()
{
	return name;
}

bool GameObject::IsEmpty()
{
	return isEmpty;
}

int GameObject::GetNumberOfComponents()
{
	return components.size();
}

Component* GameObject::GetComponentById(int id)
{
	return components[id];
}

void GameObject::SetName(std::string name)
{
	this->name = name;
}

void GameObject::SetTransform(Transform* transform)
{
	delete components[0];
	components[0] = transform;
}
