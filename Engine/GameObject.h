#pragma once
#include <d3d11.h>
#include <vector>
#include "Object.h"
#include "Component.h"
#include "Mesh.h"
#include "MeshRenderer.h"

class GameObject : public Object
{
private:
	Mesh *mesh = nullptr;
	MeshRenderer *renderer = nullptr;

	bool isEmpty = true;

	std::string name;

	std::vector<Component *> components;

public:
	GameObject();
	~GameObject();

	void Init(ID3D11Device *dev, ID3D11DeviceContext *devcon);

	void Start();
	void Update(GameTime gameTime);
	void Render();

	// get
	Transform *GetTransform();
	Mesh *GetMesh();
	MeshRenderer *GetMeshRenderer();
	std::string GetName();
	bool IsEmpty();

	// set
	void SetMesh(Mesh *mesh);
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