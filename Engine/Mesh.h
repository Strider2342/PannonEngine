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

class GameObject;
class Mesh
{
private:
	GameObject *gameObject = nullptr;

	std::vector<Vertex> vertices;
	std::vector<DWORD> indices;

public:
	Mesh();
	~Mesh();

	void Init(GameObject *gameObject);

	void Sajt()
	{
		std::cout << "Mesh!" << std::endl;
	}
};