#include "GameObject.h"

GameObject::GameObject()
{
	type = Type::EmptyObject;

	transform = new Transform();
}
GameObject::~GameObject()
{
	delete transform;
	delete mesh;
	delete renderer;

	transform = nullptr;
	mesh = nullptr;
	renderer = nullptr;
}

void GameObject::InitEmpty()
{
	type = Type::EmptyObject;

	transform = new Transform();
}
void GameObject::InitMesh()
{
	type = Type::MeshObject;

	mesh = new Mesh();
	renderer = new MeshRenderer();
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

std::string GameObject::GetName()
{
	return name;
}
