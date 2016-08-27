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
	Material(ID3D11Device *dev, ID3D11DeviceContext *devcon);
	~Material();

	ID3D11ShaderResourceView *GetTexture();
	
	void SetTexture(Texture *texture);
	void SetShader(Shader *shader);
};