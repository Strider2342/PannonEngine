#include "GameObject.h"

GameObject::GameObject()
{
	type = Type::EmptyObject;
}
GameObject::~GameObject()
{
	delete mesh;
	delete renderer;

	mesh = nullptr;
	renderer = nullptr;
}

void GameObject::InitEmpty()
{
	type = Type::EmptyObject;

	this->dev = dev;
	this->devcon = devcon;
}
void GameObject::InitMesh(ID3D11Device *dev, ID3D11DeviceContext *devcon)
{
	type = Type::MeshObject;

	this->dev = dev;
	this->devcon = devcon;

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

void GameObject::SetMesh(Mesh *mesh)
{
	this->mesh = mesh;
	renderer->SetMesh(mesh);
	renderer->SetTransform(transform);
	renderer->Init(dev, devcon);
}
