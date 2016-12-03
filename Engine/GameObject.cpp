#include "GameObject.h"

GameObject::GameObject()
{
	SetName("GameObject");
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

void GameObject::Destroy()
{
	//for (int i = 0; i < components.size(); i++)
	//{
	//	delete components.at(i);
	//}
	components.clear();

	exists = false;
}

void GameObject::OnCollision()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->OnCollision();
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

int GameObject::GetNumberOfComponents()
{
	return components.size();
}

Component* GameObject::GetComponentById(int id)
{
	return components[id];
}

bool GameObject::GetExists()
{
	return exists;
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

std::vector<GameObject*>* GameObject::GetGameObjects()
{
	return gameObjects;
}

void GameObject::SetGameObjects(std::vector<GameObject*>* gameObjects)
{
	this->gameObjects = gameObjects;
}
