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
	delete camera;
	delete light;

	transform = nullptr;
	mesh = nullptr;
	renderer = nullptr;
	camera = nullptr;
	light = nullptr;
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
void GameObject::InitCamera()
{
	type = Type::CameraObject;

	camera = new Camera();
}
void GameObject::InitLight()
{
	type = Type::LightObject;

	light = new Light();
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
Camera * GameObject::GetCamera()
{
	return camera;
}
Light * GameObject::GetLight()
{
	return light;
}
