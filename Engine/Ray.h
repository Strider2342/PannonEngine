#pragma once
#include <DirectXMath.h>

class Ray
{
private:
	DirectX::XMFLOAT3 origin;
	DirectX::XMFLOAT3 direction;

public:
	Ray();
	Ray(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction);

	// get
	DirectX::XMFLOAT3& GetOrigin();
	DirectX::XMFLOAT3& GetDirection();

	// set
	void SetOrigin(DirectX::XMFLOAT3 origin);
	void SetDirection(DirectX::XMFLOAT3 direction);
};