#include "Collider.h"

// collider
Collider::Collider()
{
	center = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
}
DirectX::XMFLOAT3& Collider::GetCenter()
{
	return center;
}
void Collider::SetCenter(DirectX::XMFLOAT3 center)
{
	this->center = center;
}

// sphere collider
SphereCollider::SphereCollider()
{
	radius = 1.0f;
}
float& SphereCollider::GetRadius()
{
	return radius;
}
void SphereCollider::SetRadius(float radius)
{
	this->radius = radius;
}

// box collider
BoxCollider::BoxCollider()
{ 
	size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
}
DirectX::XMFLOAT3& BoxCollider::GetSize()
{
	return size;
}
void BoxCollider::SetSize(DirectX::XMFLOAT3 size)
{
	this->size = size;
}
