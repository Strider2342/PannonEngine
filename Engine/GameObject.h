#pragma once
#include "Mesh.h"
#include "Transform.h"
#include "MeshRenderer.h"

class GameObject
{
public:
	static enum Type
	{
		EmptyObject,
		MeshObject,
		CameraObject,
		LightObject
	};

private:
	Type type;

	Mesh *mesh = nullptr;
	Transform *transform = nullptr;
	MeshRenderer *renderer = nullptr;

public:
	GameObject();
	~GameObject();

	void Init();

	Transform *GetTransform();
	Mesh *GetMesh();
	MeshRenderer *GetMeshRenderer();
};