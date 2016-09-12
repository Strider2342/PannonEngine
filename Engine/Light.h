#pragma once
#include <DirectXMath.h>
#include "Object.h"

class Light : public Object
{
public:
	static enum Type
	{
		Directional,
		Point,
		Spot
	};

private:
	Type type;
	
	DirectX::XMFLOAT3 color;
	float spotAngle;
	float attenuation;
	float intensity;

public:
	Light();
};