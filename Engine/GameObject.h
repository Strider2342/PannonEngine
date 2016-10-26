#pragma once
#include <d3d11.h>
#include <vector>
#include "Object.h"
#include "Transform.h"
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
	void PreUpdate();
	void Update(GameTime gameTime);
	void PostUpdate();
	void Render();
	void PostRender();

	virtual void OnCollision();
	virtual void OnCollisionEnter();
	virtual void OnCollisionStay();
	virtual void OnCollisionExit();

	// get
	Transform *GetTransform();
	std::string GetName();
	bool IsEmpty();
	int GetNumberOfComponents();
	Component* GetComponentById(int id);

	// set
	void SetName(std::string name);

	template <class T>
	void AddComponent();

	template <class T>
	void AddComponent(T *component);

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
	//component->Set
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