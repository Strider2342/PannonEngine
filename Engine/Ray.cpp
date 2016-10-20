#include "Ray.h"

Ray::Ray()
{
	origin = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	direction = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
}

Ray::Ray(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction)
{
	this->origin = origin;
	this->direction = direction;
}

DirectX::XMFLOAT3& Ray::GetOrigin()
{
	return origin;
}

DirectX::XMFLOAT3& Ray::GetDirection()
{
	return direction;
}

void Ray::SetOrigin(DirectX::XMFLOAT3 origin)
{
	this->origin = origin;
}

void Ray::SetDirection(DirectX::XMFLOAT3 direction)
{
	this->direction = direction;
}
