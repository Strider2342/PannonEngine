#pragma once
#include <DirectXMath.h>
#include "Collider.h"

struct Hit
{
	DirectX::XMFLOAT3 position;
	bool hitOccured = false;
};

class Ray : public Collider
{
	DirectX::XMFLOAT3 origin;
	DirectX::XMFLOAT3 direction;
	float distance;

public:
	Ray();
};