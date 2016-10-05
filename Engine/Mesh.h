#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <DirectXMath.h>
#include "Bounds3D.h"

struct Vertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 uv;
};

class Mesh
{
private:
	std::vector<Vertex> vertices;
	std::vector<DWORD> indices;

	Bounds3D bounds;

public:
	Mesh();
	~Mesh();

	// get
	std::vector<Vertex>& GetVertices();
	std::vector<DWORD>& GetIndices();

	// set
	void SetBounds();

	void SetVertices(std::vector<Vertex> &vertices);
	void SetIndices(std::vector<DWORD> &indices);
};