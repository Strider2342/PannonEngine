#pragma once
#include <iostream>
#include <algorithm>
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include "GameObject.h"
#include "Transform.h"
#include "Component.h"

class Collider : public Component
{
protected:
	DirectX::XMFLOAT3 center;
	
public:
	Collider();

	// get
	DirectX::XMFLOAT3& GetCenter();

	// set
	void SetCenter(DirectX::XMFLOAT3 center);

	virtual void Start();
	virtual void Update();

	virtual bool Colliding(DirectX::BoundingSphere *collider2);
	virtual bool Colliding(DirectX::BoundingOrientedBox *collider2);
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
	DirectX::BoundingSphere* GetCollider();

	// set
	void SetRadius(float radius);

	void Start();
	void Update();

	bool Colliding(DirectX::BoundingSphere *collider2);
	bool Colliding(DirectX::BoundingOrientedBox *collider2);
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
	DirectX::BoundingOrientedBox* GetCollider();

	// set
	void SetSize(DirectX::XMFLOAT3 size);

	void Start();
	void Update();

	bool Colliding(DirectX::BoundingSphere *collider2);
	bool Colliding(DirectX::BoundingOrientedBox *collider2);
};