#pragma once
#include <d3d11.h>

class Texture
{
private:
	ID3D11ShaderResourceView *texture_resource = nullptr;

public:
	Texture();
	~Texture();

	ID3D11ShaderResourceView *GetTexture();
	void SetTexture(ID3D11ShaderResourceView *texture_resource);
	void Destroy();
};