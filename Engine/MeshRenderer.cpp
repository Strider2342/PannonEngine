#include "MeshRenderer.h"

MeshRenderer::MeshRenderer()
{ }

MeshRenderer::~MeshRenderer()
{
	/*delete material;

	material = nullptr;*/
}

void MeshRenderer::Init(ID3D11Device *dev, ID3D11DeviceContext *devcon)
{
	this->dev = dev;
	this->devcon = devcon;

	material->Init(dev, devcon);
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
	material->GetShader().CreateVertexShader("defshader.hlsl", "VShader");
	material->GetShader().CreatePixelShader("defshader.hlsl", "PShader");
	material->GetShader().SetInputLayout();
}

void MeshRenderer::CreateVertexBuffer()
{

}

void MeshRenderer::CreateIndexBuffer()
{
}

void MeshRenderer::Render()
{
	DirectX::XMMATRIX matFinal;
}

Material* MeshRenderer::GetMaterial()
{
	return material;
}

Mesh* MeshRenderer::GetMesh()
{
	return mesh;
}

Camera* MeshRenderer::GetCamera()
{
	return camera;
}

void MeshRenderer::SetMaterial(Material *material)
{
	this->material = material;
}

void MeshRenderer::SetMesh(Mesh *mesh)
{
	this->mesh = mesh;
}

void MeshRenderer::SetCamera(Camera *camera)
{
	this->camera = camera;
}
