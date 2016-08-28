#pragma once
#include "Mesh.h"
#include "Transform.h"
#include "MeshRenderer.h"

class GameObject
{
private:
	Mesh *mesh = nullptr;
	Transform *transform = nullptr;
	MeshRenderer *renderer = nullptr;

public:
	GameObject();
	~GameObject();

	void Init();
	Mesh *GetMesh();

	void Sajt()
	{
		std::cout << "GameObject!" << std::endl;
	}
};