#pragma once
#include "Material.h"

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

	void SetMaterial(Material *material);
};