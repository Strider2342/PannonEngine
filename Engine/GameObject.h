#pragma once
#include <d3d11.h>
#include <vector>
#include "Input.h"
#include "Object.h"
#include "Component.h"
#include "Transform.h"

class GameObject : public Object
{
private:
	bool exists = true;

	std::string name;

	std::vector<GameObject *> *gameObjects;
	std::vector<Component *> components;

public:
	GameObject();
	~GameObject();

	void Start();
	void PreUpdate();
	void Update(GameTime gameTime, Input input);
	void PostUpdate();
	void Render();
	void PostRender();

	void Destroy();

	virtual void OnCollision();

	// get
	Transform *GetTransform();
	std::string GetName();
	int GetNumberOfComponents();
	Component* GetComponentById(int id);
	bool GetExists();

	// set
	void SetName(std::string name);
	void SetTransform(Transform *transform);

	std::vector<GameObject *>* GetGameObjects();
	void SetGameObjects(std::vector<GameObject *> *gameObjects);

	template <class T>
	void AddComponent();

	template <class T>
	void AddComponent(T *component);

	template <class T>
	void RemoveComponent();

	template <class T>
	bool HasComponent();

	template <class T>
	T* GetComponent();
};

template<class T>
inline void GameObject::AddComponent()
{
	T *component = new T();
	components.push_back(component);
	component->SetGameObject(this);
}

template<class T>
inline void GameObject::AddComponent(T *component)
{
	components.push_back(component);
	component->SetGameObject(this);
}

template<class T>
inline void GameObject::RemoveComponent()
{
	for (int i = 0; i < components.size(); i++)
	{
		if (dynamic_cast<T*>(components[i]))
		{
			components.erase(components.begin() + i);
		}
	}
}

template<class T>
inline bool GameObject::HasComponent()
{
	for (int i = 0; i < components.size(); i++)
	{
		if (dynamic_cast<T*>(components[i]))
		{
			return true;
		}
	}
	return false;
}

template<class T>
inline T * GameObject::GetComponent()
{
	for (int i = 0; i < components.size(); i++)
	{
		T *temp = dynamic_cast<T*>(components[i]);

		if (temp != nullptr)
			return temp;
	}
	return nullptr;
}