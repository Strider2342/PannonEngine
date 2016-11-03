#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include "GameObject.h"
#include "Transform.h"
#include "Component.h"
#include "MeshRenderer.h"

class Collider : public Component
{
protected:
	DirectX::ContainmentType collision;
	DirectX::XMFLOAT3 center;
	
public:
	Collider();

	// get
	virtual DirectX::XMFLOAT3& GetCenter();

	// set
	virtual void SetCenter(DirectX::XMFLOAT3 center);

	virtual void Start();
	virtual void Update(GameTime gameTime, Input input);

	virtual bool Colliding(DirectX::BoundingSphere *collider2);
	virtual bool Colliding(DirectX::BoundingOrientedBox *collider2);
};

class SphereCollider : public Collider
{
	DirectX::BoundingSphere collider;

	float radius;

public:
	SphereCollider();

	// get
	DirectX::XMFLOAT3& GetCenter();
	float& GetRadius();
	DirectX::BoundingSphere* GetCollider();

	// set
	void SetCenter(DirectX::XMFLOAT3 center);
	void SetRadius(float radius);

	void Start();
	void Update(GameTime gameTime, Input input);

	bool Colliding(DirectX::BoundingSphere *collider2);
	bool Colliding(DirectX::BoundingOrientedBox *collider2);

	// object
	std::string Export();
	void Import(const Value &component);
};

class BoxCollider : public Collider
{
	DirectX::BoundingOrientedBox collider;

	DirectX::XMFLOAT3 size;

public:
	BoxCollider();

	// get
	DirectX::XMFLOAT3& GetCenter();
	DirectX::XMFLOAT3& GetSize();
	DirectX::BoundingOrientedBox* GetCollider();

	// set
	void SetCenter(DirectX::XMFLOAT3 center);
	void SetSize(DirectX::XMFLOAT3 size);

	void Start();
	void Update(GameTime gameTime, Input input);

	bool Colliding(DirectX::BoundingSphere *collider2);
	bool Colliding(DirectX::BoundingOrientedBox *collider2);

	// object
	std::string Export();
	void Import(const Value &component);
};

class MeshCollider : public Collider
{
private:
	//std::vector<DirectX::B

public:
	MeshCollider();
};