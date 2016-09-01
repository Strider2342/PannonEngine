#include "Mesh.h"

Mesh::Mesh()
{ }

Mesh::~Mesh()
{
	//gameObject = nullptr;
}

void Mesh::Init(GameObject *gameObject)
{
	this->gameObject = gameObject;
}

GameObject* Mesh::GetGameObject()
{
	return gameObject;
}