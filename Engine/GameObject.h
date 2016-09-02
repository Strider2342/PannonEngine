#pragma onc
#include <d3d11.h>
#include "Transform.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Light.h"
#include "Camera.h"
#include "Script.h"

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

	Transform *transform = nullptr;	
	Mesh *mesh = nullptr;
	MeshRenderer *renderer = nullptr;
	Camera *camera = nullptr;
	Light *light = nullptr;

public:
	GameObject();
	~GameObject();

	void InitEmpty();
	void InitMesh();
	void InitCamera();
	void InitLight();

	Transform *GetTransform();
	Mesh *GetMesh();
	MeshRenderer *GetMeshRenderer();
	Camera *GetCamera();
	Light *GetLight();
};