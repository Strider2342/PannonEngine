#pragma once
#include <iostream>
#include "Texture.h"
#include "Mesh.h"

class ContentManager
{
private:
	ID3D11Device *dev;
	ID3D11DeviceContext *devcon;

public:
	ContentManager();

	void Init(ID3D11Device *dev, ID3D11DeviceContext *devcon);
	Texture LoadTexture(std::string filename);
	Mesh LoadMesh(std::string filename);
};