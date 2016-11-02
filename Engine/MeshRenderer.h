#pragma once
#include <vector>
#include "GameObject.h"
#include "Component.h"
#include "Mesh.h"
#include "Transform.h"
#include "Light.h"
#include "Material.h"
#include "Camera.h"

struct PerObjectCB
{
	DirectX::XMMATRIX worldMatrix;
	DirectX::XMMATRIX inverseTransposeWorldMatrix;
	DirectX::XMMATRIX WVP;
};

struct MaterialCB
{
	Material::ShaderInput input;
};

struct LightCB
{
	DirectX::XMFLOAT3 eyePosition;
	float padding1 = 1.0f;
	DirectX::XMFLOAT3 globalAmbient;
	float padding2 = 1.0f;
	Light::ShaderInput lights[8];
};

class MeshRenderer : public Component
{
private:
	ID3D11Device *dev;
	ID3D11DeviceContext *devcon;

	ID3D11Buffer *pVBuffer = nullptr;
	ID3D11Buffer *pIBuffer = nullptr;
	ID3D11Buffer *pCBufferPerObject = nullptr;
	ID3D11Buffer *pCBufferMaterial = nullptr;
	ID3D11Buffer *pCBufferLights = nullptr;

	std::vector<Light::ShaderInput> *lights;
	Material *material;
	ID3D11SamplerState *sampler;

	PerObjectCB perObjectCB;
	MaterialCB materialCB;
	LightCB lightCB;

	Mesh *mesh;
	Transform *transform;
	Camera *camera;

	std::vector<Triangle> triangles;

public:
	MeshRenderer();
	~MeshRenderer();

	void InitComponent();

	void Init(ID3D11Device *dev, ID3D11DeviceContext *devcon);
	void Start();
	void InitPipeline();
	void LoadShader();
	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void CreateSampler();
	void CreateConstantBuffers();
	void SetConstantBuffers();

	void Render();

	Material *GetMaterial();
	Mesh *GetMesh();
	Transform *GetTransform();
	Camera *GetCamera();

	// mesh
	Bounds3D& GetBounds();
	std::vector<Triangle>& GetTriangles();

	void SetMaterial(Material *material);
	void SetMesh(Mesh *mesh);
	void SetCamera(Camera *camera);
	void SetLights(std::vector<Light::ShaderInput> *lights);
};