#pragma once
#include <DirectXCollision.h>
#include "Component.h"

struct SphereCollider
{
	DirectX::BoundingSphere sphere;
	DirectX::ContainmentType collision;
};

struct BoxCollider
{
	DirectX::BoundingOrientedBox box;
	DirectX::ContainmentType collision;
};

class Collider : public Component
{
	
public:
	Collider();
};