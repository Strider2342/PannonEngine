#include "GameObject.h"

GameObject::GameObject()
{ }

GameObject::~GameObject()
{
	delete mesh;
	delete renderer;

	mesh = nullptr;
	renderer = nullptr;
}

void GameObject::Init(ID3D11Device *dev, ID3D11DeviceContext *devcon)
{
	this->dev = dev;
	this->devcon = devcon;

	renderer = new MeshRenderer();
	renderer->Init(dev, devcon);
	renderer->SetTransform(transform);

	if (!isEmpty)
	{
		mesh = new Mesh();
		renderer->Start();
	}
}

void GameObject::Start()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Start();
	}
}
void GameObject::Update()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Update();
	}
}
void GameObject::Render()
{
	if (!isEmpty)
	{
		renderer->Render();
	}
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

bool GameObject::IsEmpty()
{
	return isEmpty;
}

void GameObject::SetMesh(Mesh *mesh)
{
	isEmpty = false;
	this->mesh = mesh;
	renderer->SetMesh(mesh);
}

void GameObject::SetName(std::string name)
{
	this->name = name;
}
