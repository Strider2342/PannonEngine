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
	DirectX::BoundingSphere sphere;
	DirectX::ContainmentType collision;

	float radius;

public:
	SphereCollider();

	// get
	float& GetRadius();

	// set
	void SetRadius(float radius);
};

class BoxCollider : public Collider
{
	DirectX::BoundingOrientedBox box;
	DirectX::ContainmentType collision;

	DirectX::XMFLOAT3 size;

public:
	BoxCollider();

	// get
	DirectX::XMFLOAT3& GetSize();

	// set
	void SetSize(DirectX::XMFLOAT3 size);
};