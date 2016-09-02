#pragma once
#include <iostream>
#include "stb_image.h"
#include "Texture.h"
#include "Mesh.h"

#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>

class ContentManager
{
private:
	ID3D11Device *dev;
	ID3D11DeviceContext *devcon;

public:
	ContentManager();

	void Init(ID3D11Device *dev, ID3D11DeviceContext *devcon);
	Texture* LoadTexture(std::string filename);
	Mesh* LoadMesh(std::string filename);
};