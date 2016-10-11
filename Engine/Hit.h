#pragma once
#include <DirectXMath.h>
#include "GameObject.h"

struct Hit
{
	GameObject *gameObject;
	DirectX::XMFLOAT3 position;
	bool hitOccured = false;
};