#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Transform.h"
#include "Material.h"
#include "Camera.h"

struct CBUFFER
{
	DirectX::XMMATRIX final;
	DirectX::XMMATRIX rotation;
	DirectX::XMVECTOR lightvector;
	DirectX::XMVECTOR lightcolor;
	DirectX::XMVECTOR ambientcolor;
};

class MeshRenderer : public Component
{
private:
	ID3D11Device *dev;
	ID3D11DeviceContext *devcon;

	ID3D11Buffer *pVBuffer = nullptr;
	ID3D11Buffer *pIBuffer = nullptr;
	ID3D11Buffer *pCBuffer = nullptr;

	Material *material;
	CBUFFER cBuffer;

	Mesh *mesh;
	Transform *transform;
	Camera *camera;

public:
	MeshRenderer();
	~MeshRenderer();

	void Init(ID3D11Device *dev, ID3D11DeviceContext *devcon);
	void Start();
	void InitPipeline();
	void LoadShader();
	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void CreateConstantBuffer();
	void SetConstantBuffer();

	void Render();

	Material *GetMaterial();
	Mesh *GetMesh();
	Transform *GetTransform();
	Camera *GetCamera();

	void SetMaterial(Material *material);
	void SetMesh(Mesh *mesh);
	void SetTransform(Transform *transform);
	void SetCamera(Camera *camera);
};