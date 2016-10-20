#pragma once
#include <DirectXMath.h>

class Bounds3D
{
	DirectX::XMFLOAT2 xBounds;
	DirectX::XMFLOAT2 yBounds;
	DirectX::XMFLOAT2 zBounds;

public:
	Bounds3D();

	// get
	DirectX::XMFLOAT2& GetXBounds();
	DirectX::XMFLOAT2& GetYBounds();
	DirectX::XMFLOAT2& GetZBounds();

	DirectX::XMFLOAT3& GetCenter();

	// set
	void SetXBounds(float min, float max);
	void SetYBounds(float min, float max);
	void SetZBounds(float min, float max);
};