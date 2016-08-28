#include "MeshRenderer.h"

MeshRenderer::MeshRenderer()
{ }

MeshRenderer::~MeshRenderer()
{
	delete material;

	material = nullptr;
}

void MeshRenderer::Init(ID3D11Device *dev, ID3D11DeviceContext *devcon)
{
	this->dev = dev;
	this->devcon = devcon;
}

void MeshRenderer::InitPipeline()
{
	D3D11_BUFFER_DESC bd;

	// constant buffer		
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(cBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	dev->CreateBuffer(&bd, NULL, &pCBuffer);
}

void MeshRenderer::LoadShader()
{

}

void MeshRenderer::Render()
{

}

void MeshRenderer::SetMaterial(Material *material)
{
	this->material = material;
}