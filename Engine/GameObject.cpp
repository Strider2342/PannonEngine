#include "GameObject.h"

GameObject::GameObject()
{
	mesh = new Mesh();
	transform = new Transform();
	renderer = new MeshRenderer();
}

GameObject::~GameObject()
{
	delete mesh;
	delete transform;
	delete renderer;

	mesh = nullptr;
	transform = nullptr;
	renderer = nullptr;
}

Mesh* GameObject::GetMesh()
{
	return mesh;
}