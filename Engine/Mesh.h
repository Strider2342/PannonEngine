#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <DirectXMath.h>
#include "Triangle.h"
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
	std::vector<Triangle> triangles;

	Bounds3D bounds;

	std::string path;

public:
	Mesh();
	~Mesh();

	// get
	Bounds3D& GetBounds();

	std::vector<Vertex>& GetVertices();
	std::vector<DWORD>& GetIndices();
	std::vector<Triangle>& GetTriangles();

	std::string GetPath();

	// set
	void SetBounds();
	void SetTriangles();

	void SetVertices(std::vector<Vertex> &vertices);
	void SetIndices(std::vector<DWORD> &indices);

	void SetPath(std::string path);
};