#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"

struct QuadVertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT2 uv;
};

class PostProcess
{
	struct CBUFFER
	{
		DirectX::XMMATRIX MAT;
	};

	ID3D11Device *dev;
	ID3D11DeviceContext *devcon;

	ID3D11Texture2D *renderTargetTextureMap;
	ID3D11RenderTargetView *renderTargetViewMap;
	ID3D11DepthStencilView *depthStencilView;
	ID3D11ShaderResourceView *shaderResourceViewMap;

	ID3D11Buffer *pVBuffer = nullptr;
	ID3D11Buffer *pIBuffer = nullptr;
	ID3D11Buffer *pCBuffer = nullptr;

	CBUFFER cBuffer;

	Shader shader;

	Camera *camera;

public:
	PostProcess();

	void Init(ID3D11Device *dev, ID3D11DeviceContext *devcon);

	void CreateRenderTargetTexture();
	void CreateRenderTargetView();
	void CreateDepthStencilView();
	void CreateShaderResourceView();

	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void CreateConstantBuffer();
	void SetConstantBuffer();
	void Render();

	void SetCamera(Camera *camera);
};