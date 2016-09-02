#pragma once
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

class MeshRenderer
{
private:
	ID3D11Device *dev;
	ID3D11DeviceContext *devcon;

	ID3D11Buffer *pVBuffer = nullptr;
	ID3D11Buffer *pIBuffer = nullptr;
	ID3D11Buffer *pCBuffer = nullptr;

	Material *material;
	CBUFFER cBuffer;

	Camera *camera;

public:
	MeshRenderer();
	~MeshRenderer();

	void Init(ID3D11Device *dev, ID3D11DeviceContext *devcon);
	void InitPipeline();
	void LoadShader();
	void CreateVertexBuffer();
	void CreateIndexBuffer();

	void Render();

	Material *GetMaterial();
	Camera *GetCamera();

	void SetMaterial(Material *material);
	void SetCamera(Camera *camera);
};