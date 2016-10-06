#pragma once
#include <DirectXMath.h>
#include "Ray.h"

class RayCast
{

public:
	RayCast();

	Hit Cast(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 destination);
	Hit Cast(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction, float distance);
};