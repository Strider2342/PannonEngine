#include "RayCast.h"

RayCast::RayCast()
{
}

Hit RayCast::Cast(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 destination)
{
	return Hit();
}

Hit RayCast::Cast(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction, float distance)
{
	return Hit();
}
