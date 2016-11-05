#pragma once
#include <iostream>
#include <list>
#include "GameScene.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"

#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>

class ContentManager
{
private:
	ID3D11Device *dev;
	ID3D11DeviceContext *devcon;

	std::string resourceDir;

public:
	ContentManager();

	void Init(ID3D11Device *dev, ID3D11DeviceContext *devcon);

	GameScene* LoadScene(std::string filename);
	Texture* LoadTexture(std::string filename);
	Material* LoadMaterial(std::string filename);
	Mesh* LoadMesh(std::string filename);

	void Instantiate(GameObject *prefab);
};