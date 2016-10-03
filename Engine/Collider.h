#pragma once
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include "GameObject.h"
#include "Transform.h"
#include "Component.h"

class Collider : public Component
{
	DirectX::XMFLOAT3 center;
	
public:
	Collider();

	// get
	DirectX::XMFLOAT3& GetCenter();

	// set
	void SetCenter(DirectX::XMFLOAT3 center);
};

class SphereCollider : public Collider
{
	DirectX::BoundingSphere collider;
	DirectX::ContainmentType collision;

	float radius;

public:
	SphereCollider();

	// get
	float& GetRadius();

	// set
	void SetRadius(float radius);

	bool Colliding(DirectX::BoundingSphere &collider2);
	bool Colliding(DirectX::BoundingOrientedBox &collider2);
};

class BoxCollider : public Collider
{
	DirectX::BoundingOrientedBox collider;
	DirectX::ContainmentType collision;

	DirectX::XMFLOAT3 size;

public:
	BoxCollider();

	// get
	DirectX::XMFLOAT3& GetSize();

	// set
	void SetSize(DirectX::XMFLOAT3 size);

	bool Colliding(DirectX::BoundingSphere &collider2);
	bool Colliding(DirectX::BoundingOrientedBox &collider2);
};