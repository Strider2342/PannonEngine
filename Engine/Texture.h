#pragma once
#include <iostream>
#include <d3d11.h>
#include "stb_image.h"

class Texture
{
private:
	ID3D11ShaderResourceView *texture_resource = nullptr;

	std::string path;

public:
	Texture();
	~Texture();

	ID3D11ShaderResourceView *GetTexture();
	void SetTexture(ID3D11ShaderResourceView *texture_resource);
	void Destroy();

	std::string GetPath();
	void SetPath(std::string path);
};