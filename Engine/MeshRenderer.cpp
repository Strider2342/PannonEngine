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
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex) * mesh->GetVertices().size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	dev->CreateBuffer(&bd, NULL, &pVBuffer);

	D3D11_MAPPED_SUBRESOURCE ms;
	devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, &(mesh->GetVertices())[0], sizeof(Vertex) * mesh->GetVertices().size());
	devcon->Unmap(pVBuffer, NULL);
}

void MeshRenderer::CreateIndexBuffer()
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(DWORD) * mesh->GetIndices().size();
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	dev->CreateBuffer(&bd, NULL, &pIBuffer);

	D3D11_MAPPED_SUBRESOURCE ms;
	devcon->Map(pIBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, mesh->GetIndices().data(), sizeof(DWORD) * mesh->GetIndices().size());
	devcon->Unmap(pIBuffer, NULL);
}

void MeshRenderer::Render()
{
	DirectX::XMMATRIX matFinal = transform->GetWorldMatrix() * camera->GetViewMatrix() * camera->GetProjectionMatrix();

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	/*devcon->VSSetShader(pVS, 0, 0);
	devcon->PSSetShader(pPS, 0, 0);
	devcon->IASetInputLayout(pLayout);
	devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
	devcon->IASetIndexBuffer(pIBuffer, DXGI_FORMAT_R32_UINT, 0);*/
}

Material* MeshRenderer::GetMaterial()
{
	return material;
}

Mesh* MeshRenderer::GetMesh()
{
	return mesh;
}

Transform* MeshRenderer::GetTransform()
{
	return transform;
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

void MeshRenderer::SetTransform(Transform *transform)
{
	this->transform = transform;
}

void MeshRenderer::SetCamera(Camera *camera)
{
	this->camera = camera;
}
