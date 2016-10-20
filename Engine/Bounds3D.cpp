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
	return DirectX::XMFLOAT3(xBounds.y - xBounds.x, yBounds.y - yBounds.x, zBounds.y - zBounds.x);
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