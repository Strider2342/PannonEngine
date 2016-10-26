#include "MeshRenderer.h"

MeshRenderer::MeshRenderer()
{ 
}

MeshRenderer::~MeshRenderer()
{
	/*delete material;

	material = nullptr;*/
}

void MeshRenderer::InitComponent()
{
	transform = gameObject->GetTransform();
}

void MeshRenderer::Init(ID3D11Device *dev, ID3D11DeviceContext *devcon)
{
	this->dev = dev;
	this->devcon = devcon;

	mesh = new Mesh();

	material = new Material();
	material->Init(dev, devcon);	
}

void MeshRenderer::Start()
{ 
	transform = gameObject->GetTransform();
}

void MeshRenderer::InitPipeline()
{
	CreateVertexBuffer();
	CreateIndexBuffer();
	CreateSampler();
	CreateConstantBuffers();

	LoadShader();
}

void MeshRenderer::LoadShader()
{
	material->GetShader().LoadVertexShaderFromFile(L"../Shaders/Phong.hlsl", "VShader");
	material->GetShader().LoadPixelShaderFromFile(L"../Shaders/Phong.hlsl", "PShader");
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

void MeshRenderer::CreateSampler()
{
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.BorderColor[0] = 1.0f;
	samplerDesc.BorderColor[1] = 1.0f;
	samplerDesc.BorderColor[2] = 1.0f;
	samplerDesc.BorderColor[3] = 1.0f;
	samplerDesc.MinLOD = -FLT_MAX;
	samplerDesc.MaxLOD = FLT_MAX;

	dev->CreateSamplerState(&samplerDesc, &sampler);
}

void MeshRenderer::CreateConstantBuffers()
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	// per object
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(perObjectCB);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	dev->CreateBuffer(&bd, NULL, &pCBufferPerObject);

	// material
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(materialCB);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	dev->CreateBuffer(&bd, NULL, &pCBufferMaterial);

	// light
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(lightCB);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	dev->CreateBuffer(&bd, NULL, &pCBufferLights);
}

void MeshRenderer::SetConstantBuffers()
{
	DirectX::XMMATRIX inverseTransposeWorldMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(NULL, transform->GetWorldMatrix()));
	
	DirectX::XMMATRIX matWorld = transform->GetWorldMatrix();
	DirectX::XMMATRIX matView = camera->GetViewMatrix();
	DirectX::XMMATRIX matProjection = camera->GetProjectionMatrix();
	DirectX::XMMATRIX WVP = matWorld * matView * matProjection;

	perObjectCB.worldMatrix = transform->GetWorldMatrix();
	perObjectCB.inverseTransposeWorldMatrix = inverseTransposeWorldMatrix;
	perObjectCB.WVP = WVP;

	lightCB.eyePosition = camera->GetTransform()->GetPosition();
	lightCB.globalAmbient = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < lights->size(); i++)
	{
		Light::ShaderInput lightInput = lights->at(i);
		lightCB.lights[i] = lightInput;
	}

	Material::ShaderInput materialInput = material->GetShaderInput();
	materialCB.input = materialInput;
}

void MeshRenderer::Render()
{
	SetConstantBuffers();

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	ID3D11VertexShader *vs = material->GetShader().GetVertexShader();
	ID3D11PixelShader *ps = material->GetShader().GetPixelShader();
	ID3D11InputLayout *layout = material->GetShader().GetLayout();
	ID3D11ShaderResourceView *pTexture = nullptr;

	devcon->VSSetShader(vs, 0, 0);
	devcon->PSSetShader(ps, 0, 0);
	devcon->IASetInputLayout(layout);
	devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
	devcon->IASetIndexBuffer(pIBuffer, DXGI_FORMAT_R32_UINT, 0);

	// per object
	devcon->VSSetConstantBuffers(0, 1, &pCBufferPerObject);
	devcon->UpdateSubresource(pCBufferPerObject, 0, 0, &perObjectCB, 0, 0);

	// material
	devcon->PSSetConstantBuffers(1, 1, &pCBufferMaterial);
	devcon->UpdateSubresource(pCBufferMaterial, 0, 0, &materialCB, 0, 0);

	// light
	devcon->PSSetConstantBuffers(2, 1, &pCBufferLights);
	devcon->UpdateSubresource(pCBufferLights, 0, 0, &lightCB, 0, 0);

	devcon->PSSetSamplers(0, 1, &sampler);

	if (material->HasTexture())
	{
		pTexture = material->GetTextureResource();
		devcon->PSSetShaderResources(0, 1, &pTexture);
	}

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

Bounds3D& MeshRenderer::GetBounds()
{
	Bounds3D originalBounds = mesh->GetBounds();
	Bounds3D bounds = Bounds3D();

	bounds.GetXBounds() = DirectX::XMFLOAT2(originalBounds.GetXBounds().x * gameObject->GetTransform()->GetScale().x, originalBounds.GetXBounds().y * gameObject->GetTransform()->GetScale().y);
	bounds.GetYBounds() = DirectX::XMFLOAT2(originalBounds.GetYBounds().x * gameObject->GetTransform()->GetScale().x, originalBounds.GetYBounds().y * gameObject->GetTransform()->GetScale().y);
	bounds.GetZBounds() = DirectX::XMFLOAT2(originalBounds.GetZBounds().x * gameObject->GetTransform()->GetScale().x, originalBounds.GetZBounds().y * gameObject->GetTransform()->GetScale().y);

	return bounds;
}

std::vector<Triangle>& MeshRenderer::GetTriangles()
{
	std::vector<Triangle> originaltriangles = mesh->GetTriangles();
	std::vector<Triangle> triangles = std::vector<Triangle>();

	for (int i = 0; i < triangles.size(); i++)
	{
		DirectX::XMFLOAT3 pointA = DirectX::XMFLOAT3(originaltriangles.at(i).GetPointA().x * gameObject->GetTransform()->GetScale().x, originaltriangles.at(i).GetPointA().y * gameObject->GetTransform()->GetScale().y, originaltriangles.at(i).GetPointA().z * gameObject->GetTransform()->GetScale().z);
		DirectX::XMFLOAT3 pointB = DirectX::XMFLOAT3(originaltriangles.at(i).GetPointB().x * gameObject->GetTransform()->GetScale().x, originaltriangles.at(i).GetPointB().y * gameObject->GetTransform()->GetScale().y, originaltriangles.at(i).GetPointB().z * gameObject->GetTransform()->GetScale().z);
		DirectX::XMFLOAT3 pointC = DirectX::XMFLOAT3(originaltriangles.at(i).GetPointC().x * gameObject->GetTransform()->GetScale().x, originaltriangles.at(i).GetPointC().y * gameObject->GetTransform()->GetScale().y, originaltriangles.at(i).GetPointC().z * gameObject->GetTransform()->GetScale().z);

		Triangle triangle = Triangle(pointA, pointB, pointC);
		
		triangles.push_back(triangle);
	}

	return triangles;
}

void MeshRenderer::SetMaterial(Material *material)
{
	this->material = material;
}

void MeshRenderer::SetMesh(Mesh *mesh)
{
	this->mesh = mesh;
	InitPipeline();
}

void MeshRenderer::SetCamera(Camera *camera)
{
	this->camera = camera;
}

void MeshRenderer::SetLights(std::vector<Light::ShaderInput> *lights)
{
	this->lights = lights;
}
