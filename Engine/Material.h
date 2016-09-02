#pragma once
#include <DirectXMath.h>
#include "Texture.h"
#include "Shader.h"

class Material
{
private:
	DirectX::XMFLOAT3 diffuse;
	DirectX::XMFLOAT3 specular;
	DirectX::XMFLOAT3 ambient;
	DirectX::XMFLOAT3 emissive;
	float power;

	Texture *texture = nullptr;
	Shader *shader = nullptr;

public:
	Material();
	~Material();

	void Init(ID3D11Device *dev, ID3D11DeviceContext *devcon);

	ID3D11ShaderResourceView *GetTextureResource();
	
	Texture& GetTexture();
	Shader& GetShader();

	DirectX::XMFLOAT3 GetDiffuse();
	DirectX::XMFLOAT3 GetSpecular();
	DirectX::XMFLOAT3 GetAmbient();
	DirectX::XMFLOAT3 GetEmissive();
	float GetPower();

	void SetTexture(Texture *texture);
	void SetShader(Shader *shader);

	void SetDiffuse(float r, float g, float b);
	void SetSpecular(float r, float g, float b);
	void SetAmbient(float r, float g, float b);
	void SetEmissive(float r, float g, float b);
	void SetPower(float value);
};