#include "PostProcess.h"

PostProcess::PostProcess()
{ }

void PostProcess::Init(ID3D11Device *dev, ID3D11DeviceContext *devcon)
{
	this->dev = dev;
	this->devcon = devcon;

	CreateRenderTargetTexture();
	CreateRenderTargetView();
	CreateDepthStencilView();
	CreateShaderResourceView();
	
	CreateVertexBuffer();
	CreateIndexBuffer();
	CreateConstantBuffer();

	shader.Init(dev, devcon);
	shader.CreateVertexShader(L"../Shaders/PostProcess.hlsl", "VShader");
	shader.CreatePixelShader(L"../Shaders/PostProcess.hlsl", "PShader");
	shader.SetInputLayoutQuad();
}

void PostProcess::CreateRenderTargetTexture()
{
	D3D11_TEXTURE2D_DESC textureDesc;

	ZeroMemory(&textureDesc, sizeof(textureDesc));

	textureDesc.Width = 1280.0f / 2.0f;
	textureDesc.Height = 720.0f / 2.0f;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	// Create the texture
	HRESULT hr = dev->CreateTexture2D(&textureDesc, NULL, &renderTargetTextureMap);
}
void PostProcess::CreateRenderTargetView()
{
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;

	renderTargetViewDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	// Create the render target view.
	HRESULT hr = dev->CreateRenderTargetView(renderTargetTextureMap, &renderTargetViewDesc, &renderTargetViewMap);
}
void PostProcess::CreateDepthStencilView()
{
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;

	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	depthStencilViewDesc.Texture2D.MipSlice = 0;;

	HRESULT hr = dev->CreateDepthStencilView(renderTargetTextureMap, &depthStencilViewDesc, &depthStencilView);
}
void PostProcess::CreateShaderResourceView()
{
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

	shaderResourceViewDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	// Create the shader resource view.
	HRESULT hr = dev->CreateShaderResourceView(renderTargetTextureMap, &shaderResourceViewDesc, &shaderResourceViewMap);
}

void PostProcess::CreateVertexBuffer()
{
	QuadVertex vertices[4] =
	{
		{ DirectX::XMFLOAT3(1, 1, 1), DirectX::XMFLOAT2(1, 0) },
		{ DirectX::XMFLOAT3(1, -1, 1), DirectX::XMFLOAT2(1, 1) },
		{ DirectX::XMFLOAT3(-1, -1, 1), DirectX::XMFLOAT2(0, 1) },
		{ DirectX::XMFLOAT3(-1, 1, 1), DirectX::XMFLOAT2(0, 0) }
	};

	D3D11_BUFFER_DESC vertexBufDesc;
	ZeroMemory(&vertexBufDesc, sizeof(vertexBufDesc));

	vertexBufDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufDesc.ByteWidth = sizeof(QuadVertex) * sizeof(vertices);
	vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	dev->CreateBuffer(&vertexBufDesc, NULL, &pVBuffer);

	D3D11_MAPPED_SUBRESOURCE ms;
	devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, &vertices[0], sizeof(Vertex) *  sizeof(vertices));
	devcon->Unmap(pVBuffer, NULL);
}
void PostProcess::CreateIndexBuffer()
{
	DWORD indices[6] = { 0, 1, 2, 2, 3, 0};

	D3D11_BUFFER_DESC indexBufDesc;
	ZeroMemory(&indexBufDesc, sizeof(indexBufDesc));
	indexBufDesc.Usage = D3D11_USAGE_DYNAMIC;
	indexBufDesc.ByteWidth = sizeof(DWORD) * sizeof(indices);
	indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	indexBufDesc.MiscFlags = 0;

	dev->CreateBuffer(&indexBufDesc, NULL, &pIBuffer);

	D3D11_MAPPED_SUBRESOURCE ms;
	devcon->Map(pIBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, indices, sizeof(DWORD) * sizeof(indices));
	devcon->Unmap(pIBuffer, NULL);
}
void PostProcess::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC constantBufDesc;
	ZeroMemory(&constantBufDesc, sizeof(constantBufDesc));

	constantBufDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufDesc.ByteWidth = sizeof(cBuffer);
	constantBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	dev->CreateBuffer(&constantBufDesc, NULL, &pCBuffer);
}

void PostProcess::SetConstantBuffer()
{
	DirectX::XMMATRIX mat = camera->GetViewMatrix() * camera->GetProjectionMatrix();
	cBuffer.MAT = XMMatrixTranspose(mat);
}

void PostProcess::Render()
{
	SetConstantBuffer();

	float clearColor[4] = { 0.0f, 0.4f, 0.8f, 1.0f };

	devcon->OMSetRenderTargets(1, &renderTargetViewMap, depthStencilView);

	devcon->ClearRenderTargetView(renderTargetViewMap, clearColor);

	devcon->UpdateSubresource(pCBuffer, 0, NULL, &cBuffer, 0, 0);

	devcon->DrawIndexed(6, 0, 0);
}

void PostProcess::SetCamera(Camera *camera)
{
	this->camera = camera;
}
