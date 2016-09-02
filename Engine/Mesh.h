#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <DirectXMath.h>

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

public:
	Mesh();
	~Mesh();

	std::vector<Vertex>& GetVertices();
	std::vector<DWORD>& GetIndices();

	void SetVertices(std::vector<Vertex> &vertices);
	void SetIndices(std::vector<DWORD> &indices);
};