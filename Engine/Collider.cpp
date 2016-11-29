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
{}
void Collider::Start()
{}
void Collider::Update(GameTime gameTime, Input input)
{}
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
DirectX::XMFLOAT3& SphereCollider::GetCenter()
{
	return center;
}
float& SphereCollider::GetRadius()
{
	return radius;
}
DirectX::BoundingSphere* SphereCollider::GetCollider()
{
	return &collider;
}
void SphereCollider::SetCenter(DirectX::XMFLOAT3 center)
{
	this->center = center;
	if (gameObject != NULL)
	{
		this->collider.Center = DirectX::XMFLOAT3(gameObject->GetTransform()->GetPosition().x + center.x, gameObject->GetTransform()->GetPosition().y + center.y, gameObject->GetTransform()->GetPosition().z + center.z);
	}
	else
	{
		this->collider.Center = DirectX::XMFLOAT3(center.x, center.y, center.z);
	}
}
void SphereCollider::SetRadius(float radius)
{
	this->radius = radius;
	collider.Radius = radius;
}
void SphereCollider::Start()
{
	float max = gameObject->GetTransform()->GetScale().x;
	if (gameObject->GetTransform()->GetScale().y > max) { max = gameObject->GetTransform()->GetScale().y; }
	if (gameObject->GetTransform()->GetScale().z > max) { max = gameObject->GetTransform()->GetScale().z; }

	XMFLOAT3 position = gameObject->GetTransform()->GetPosition();
	collider.Center = DirectX::XMFLOAT3(position.x + center.x, position.y + center.y, position.z + center.z);
	collider.Radius = radius * max;
}
void SphereCollider::Update(GameTime gameTime, Input input)
{
	float max = gameObject->GetTransform()->GetLocalScale().x;
	if (gameObject->GetTransform()->GetLocalScale().y > max) { max = gameObject->GetTransform()->GetLocalScale().y; }
	if (gameObject->GetTransform()->GetLocalScale().z > max) { max = gameObject->GetTransform()->GetLocalScale().z; }

	XMFLOAT3 position = gameObject->GetTransform()->GetPosition();
	collider.Center = DirectX::XMFLOAT3(position.x + center.x, position.y + center.y, position.z + center.z);
	collider.Radius = radius * max;
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
DirectX::XMFLOAT3& BoxCollider::GetCenter()
{
	return center;
}
DirectX::XMFLOAT3& BoxCollider::GetSize()
{
	return size;
}
DirectX::BoundingOrientedBox* BoxCollider::GetCollider()
{
	return &collider;
}
void BoxCollider::SetCenter(DirectX::XMFLOAT3 center)
{
	this->center = center;
	if (gameObject != NULL)
	{
		this->collider.Center = DirectX::XMFLOAT3(gameObject->GetTransform()->GetLocalPosition().x + center.x, gameObject->GetTransform()->GetLocalPosition().y + center.y, gameObject->GetTransform()->GetLocalPosition().z + center.z);
	}
	else
	{
		this->collider.Center = DirectX::XMFLOAT3(center.x, center.y, center.z);
	}
}
void BoxCollider::SetSize(DirectX::XMFLOAT3 size)
{
	this->size = size;
	if (gameObject != NULL)
	{
		collider.Extents = DirectX::XMFLOAT3(gameObject->GetTransform()->GetLocalScale().x * size.x, gameObject->GetTransform()->GetLocalScale().y * size.y, gameObject->GetTransform()->GetLocalScale().z * size.z);
	}
	else
	{
		this->collider.Extents = DirectX::XMFLOAT3(size.x, size.y, size.z);
	}
}
void BoxCollider::Start()
{
	collider.Center = DirectX::XMFLOAT3(gameObject->GetTransform()->GetLocalPosition().x + center.x, gameObject->GetTransform()->GetLocalPosition().y + center.y, gameObject->GetTransform()->GetLocalPosition().z + center.z);
	collider.Extents = DirectX::XMFLOAT3(gameObject->GetTransform()->GetLocalScale().x * size.x * 2.0f, gameObject->GetTransform()->GetLocalScale().y * size.y * 2.0f, gameObject->GetTransform()->GetLocalScale().z * size.z * 2.0f);
	//collider.Orientation = DirectX::XMFLOAT4(gameObject->GetTransform()->GetForward().x, gameObject->GetTransform()->GetForward().y, gameObject->GetTransform()->GetForward().z, 1.0f);
	collider.Orientation = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
}
void BoxCollider::Update(GameTime gameTime, Input input)
{
	collider.Center = DirectX::XMFLOAT3(gameObject->GetTransform()->GetLocalPosition().x + center.x, gameObject->GetTransform()->GetLocalPosition().y + center.y, gameObject->GetTransform()->GetLocalPosition().z + center.z);
	collider.Extents = DirectX::XMFLOAT3(gameObject->GetTransform()->GetLocalScale().x * size.x * 2.0f, gameObject->GetTransform()->GetLocalScale().y * size.y * 2.0f, gameObject->GetTransform()->GetLocalScale().z * size.z * 2.0f);
	//collider.Orientation = DirectX::XMFLOAT4(gameObject->GetTransform()->GetForward().x, gameObject->GetTransform()->GetForward().y, gameObject->GetTransform()->GetForward().z, 1.0f);
	collider.Orientation = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
}
bool BoxCollider::Colliding(DirectX::BoundingSphere *collider2)
{
	return collider.Intersects(*collider2);
}
bool BoxCollider::Colliding(DirectX::BoundingOrientedBox *collider2)
{
	return collider.Intersects(*collider2);
}