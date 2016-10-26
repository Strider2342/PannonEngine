#include "Bounds3D.h"

Bounds3D::Bounds3D()
{

}

DirectX::XMFLOAT2& Bounds3D::GetXBounds()
{
	return xBounds;
}
DirectX::XMFLOAT2& Bounds3D::GetYBounds()
{
	return yBounds;
}
DirectX::XMFLOAT2& Bounds3D::GetZBounds()
{
	return zBounds;
}

DirectX::XMFLOAT3& Bounds3D::GetCenter()
{
	DirectX::XMFLOAT3 center = DirectX::XMFLOAT3(xBounds.x + (GetXLength() * 0.5f), yBounds.x + (GetYLength() * 0.5f), zBounds.x + (GetZLength() * 0.5f));
	return center;
}

float Bounds3D::GetXLength()
{
	return xBounds.y - xBounds.x;
}

float Bounds3D::GetYLength()
{
	return yBounds.y - yBounds.x;
}

float Bounds3D::GetZLength()
{
	return zBounds.y - zBounds.x;
}

void Bounds3D::SetXBounds(float min, float max)
{
	xBounds = DirectX::XMFLOAT2(min, max);
}
void Bounds3D::SetYBounds(float min, float max)
{
	yBounds = DirectX::XMFLOAT2(min, max);
}
void Bounds3D::SetZBounds(float min, float max)
{
	zBounds = DirectX::XMFLOAT2(min, max);
}