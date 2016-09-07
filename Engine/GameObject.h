#pragma once
#include <d3d11.h>
#include "Object.h"
#include "Mesh.h"
#include "MeshRenderer.h"

class GameObject : public Object
{
public:
	static enum Type
	{
		EmptyObject,
		MeshObject
	};

private:
	Type type;

	Mesh *mesh = nullptr;
	MeshRenderer *renderer = nullptr;

	std::string name;

public:
	GameObject();
	~GameObject();

	void InitEmpty();
	void InitMesh(ID3D11Device *dev, ID3D11DeviceContext *devcon);

	Transform *GetTransform();
	Mesh *GetMesh();
	MeshRenderer *GetMeshRenderer();

	std::string GetName();

	void SetMesh(Mesh *mesh);
};