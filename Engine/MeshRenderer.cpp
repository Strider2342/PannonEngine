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

	CreateVertexBuffer();
	CreateIndexBuffer();
	InitPipeline();
}

void MeshRenderer::InitPipeline()
{
	CreateConstantBuffer();
		
	LoadShader();
}

void MeshRenderer::LoadShader()
{
	material->GetShader().CreateVertexShader(L"../Engine/Shaders/DefShader.hlsl", "VShader");
	material->GetShader().CreatePixelShader(L"../Engine/Shaders/DefShader.hlsl", "PShader");
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

void MeshRenderer::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(cBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	dev->CreateBuffer(&bd, NULL, &pCBuffer);
}

void MeshRenderer::SetConstantBuffer()
{
	DirectX::XMMATRIX matFinal = transform->GetWorldMatrix() * camera->GetViewMatrix() * camera->GetProjectionMatrix();

	cBuffer.final = matFinal;
	cBuffer.rotation = transform->GetRotationMatrix();
	cBuffer.lightvector = DirectX::XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	cBuffer.lightcolor = DirectX::XMVectorSet(0.1f, 0.1f, 0.1f, 1.0f);
	cBuffer.ambientcolor = DirectX::XMLoadFloat3(&material->GetAmbient());
}

void MeshRenderer::Render()
{
	DirectX::XMMATRIX matWorld = transform->GetWorldMatrix();
	DirectX::XMMATRIX matView = camera->GetViewMatrix();
	DirectX::XMMATRIX matProj = camera->GetProjectionMatrix();
	DirectX::XMMATRIX matFinal = transform->GetWorldMatrix() * camera->GetViewMatrix() * camera->GetProjectionMatrix();

	SetConstantBuffer();

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	ID3D11VertexShader *vs = material->GetShader().GetVertexShader();
	ID3D11PixelShader *ps = material->GetShader().GetPixelShader();
	ID3D11InputLayout *layout = material->GetShader().GetLayout();
	
	devcon->VSSetShader(vs, 0, 0);
	devcon->PSSetShader(ps, 0, 0);
	devcon->IASetInputLayout(layout);
	devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
	devcon->IASetIndexBuffer(pIBuffer, DXGI_FORMAT_R32_UINT, 0);

	devcon->VSSetConstantBuffers(0, 1, &pCBuffer);
	devcon->UpdateSubresource(pCBuffer, 0, 0, &matFinal, 0, 0);
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	devcon->DrawIndexed(mesh->GetIndices().size(), 0, 0);
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
