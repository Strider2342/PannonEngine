#pragma once
#include <DirectXMath.h>

class Triangle
{
private:
	DirectX::XMFLOAT3 pointA;
	DirectX::XMFLOAT3 pointB;
	DirectX::XMFLOAT3 pointC;

public:
	Triangle();
	Triangle(DirectX::XMFLOAT3 pointA, DirectX::XMFLOAT3 pointB, DirectX::XMFLOAT3 pointC);

	DirectX::XMFLOAT3& GetPointA();
	DirectX::XMFLOAT3& GetPointB();
	DirectX::XMFLOAT3& GetPointC();

	DirectX::XMFLOAT3& GetPointATransformed(DirectX::XMMATRIX &matView);
	DirectX::XMFLOAT3& GetPointBTransformed(DirectX::XMMATRIX &matView);
	DirectX::XMFLOAT3& GetPointCTransformed(DirectX::XMMATRIX &matView);
};