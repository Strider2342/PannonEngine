#include "GameObject.h"

GameObject::GameObject()
{
	type = Type::EmptyObject;

	transform = new Transform();
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

Transform* GameObject::GetTransform()
{
	return transform;
}

Mesh* GameObject::GetMesh()
{
	return mesh;
}

MeshRenderer* GameObject::GetMeshRenderer()
{
	return renderer;
}
