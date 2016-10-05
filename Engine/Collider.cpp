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
void Collider::Start()
{

}
void Collider::Update()
{

}
bool Collider::Colliding(DirectX::BoundingSphere *collider2)
{
	return false;
}
bool Collider::Colliding(DirectX::BoundingOrientedBox *collider2)
{
	return false;
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
DirectX::BoundingSphere* SphereCollider::GetCollider()
{
	return &collider;
}
void SphereCollider::SetRadius(float radius)
{
	this->radius = radius;
}
void SphereCollider::Start()
{
	collider.Center = DirectX::XMFLOAT3(gameObject->GetTransform()->GetPosition().x + center.x, gameObject->GetTransform()->GetPosition().y + center.y, gameObject->GetTransform()->GetPosition().z + center.z);
	collider.Radius = radius;
}
void SphereCollider::Update()
{
	collider.Center = DirectX::XMFLOAT3(gameObject->GetTransform()->GetPosition().x + center.x, gameObject->GetTransform()->GetPosition().y + center.y, gameObject->GetTransform()->GetPosition().z + center.z);
	collider.Radius = radius;
}
bool SphereCollider::Colliding(DirectX::BoundingSphere *collider2)
{
	return collider.Intersects(*collider2);
}
bool SphereCollider::Colliding(DirectX::BoundingOrientedBox *collider2)
{
	return collider.Intersects(*collider2);
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
DirectX::BoundingOrientedBox* BoxCollider::GetCollider()
{
	return &collider;
}
void BoxCollider::SetSize(DirectX::XMFLOAT3 size)
{
	this->size = size;
}
void BoxCollider::Start()
{
	collider.Center = DirectX::XMFLOAT3(gameObject->GetTransform()->GetPosition().x + center.x, gameObject->GetTransform()->GetPosition().y + center.y, gameObject->GetTransform()->GetPosition().z + center.z);
	collider.Extents = DirectX::XMFLOAT3(gameObject->GetTransform()->GetScale().x * size.x, gameObject->GetTransform()->GetScale().y * size.y, gameObject->GetTransform()->GetScale().z * size.z);
	collider.Orientation = DirectX::XMFLOAT4(gameObject->GetTransform()->GetForward().x, gameObject->GetTransform()->GetForward().y, gameObject->GetTransform()->GetForward().z, 1.0f);
}
void BoxCollider::Update()
{
	collider.Center = DirectX::XMFLOAT3(gameObject->GetTransform()->GetPosition().x + center.x, gameObject->GetTransform()->GetPosition().y + center.y, gameObject->GetTransform()->GetPosition().z + center.z);
	collider.Extents = DirectX::XMFLOAT3(gameObject->GetTransform()->GetScale().x * size.x, gameObject->GetTransform()->GetScale().y * size.y, gameObject->GetTransform()->GetScale().z * size.z);
	collider.Orientation = DirectX::XMFLOAT4(gameObject->GetTransform()->GetForward().x, gameObject->GetTransform()->GetForward().y, gameObject->GetTransform()->GetForward().z, 1.0f);
}
bool BoxCollider::Colliding(DirectX::BoundingSphere *collider2)
{
	return collider.Intersects(*collider2);
}
bool BoxCollider::Colliding(DirectX::BoundingOrientedBox *collider2)
{
	return collider.Intersects(*collider2);
}
