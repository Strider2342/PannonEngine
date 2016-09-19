#pragma once
#include <d3d11.h>
#include <vector>
#include "Object.h"
#include "Script.h"
#include "Mesh.h"
#include "MeshRenderer.h"

class GameObject : public Object
{
private:
	Mesh *mesh = nullptr;
	MeshRenderer *renderer = nullptr;

	bool isEmpty = true;

	std::string name;

	std::vector<Script *> scripts;

public:
	GameObject();
	~GameObject();

	void Init(ID3D11Device *dev, ID3D11DeviceContext *devcon);

	void Start();
	void Update();
	void Render();

	Transform *GetTransform();
	Mesh *GetMesh();
	MeshRenderer *GetMeshRenderer();
	std::string GetName();

	bool IsEmpty();

	void SetMesh(Mesh *mesh);
	void SetName(std::string name);

	template <class T>
	void AddScript();

	template <class T>
	T* GetScript();
};

template<class T>
inline void GameObject::AddScript()
{
	T *script = new T();
	scripts.push_back(script);
	script->SetGameObject(this);
}

template<class T>
inline T * GameObject::GetScript()
{
	for (int i = 0; i < scripts.size(); i++)
	{
		T *temp = dynamic_cast<T*>(scripts[i]);

		if (temp != NULL)
			return temp;
	}
	return NULL;
}
