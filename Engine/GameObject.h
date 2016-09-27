#pragma once
#include <d3d11.h>
#include <vector>
#include "Object.h"
#include "Component.h"

class GameObject : public Object
{
private:
	bool isEmpty = true;

	std::string name;

	std::vector<Component *> components;

public:
	GameObject();
	~GameObject();

	void Start();
	void Update(GameTime gameTime);
	void Render();

	// get
	Transform *GetTransform();
	std::string GetName();
	bool IsEmpty();

	// set
	void SetName(std::string name);

	template <class T>
	void AddComponent();

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
inline T * GameObject::GetComponent()
{
	for (int i = 0; i < components.size(); i++)
	{
		T *temp = dynamic_cast<T*>(components[i]);

		if (temp != NULL)
			return temp;
	}
	return NULL;
}