#pragma once
#include <DirectXMath.h>
#include "Object.h"

class Light : public Object
{
public:
	static enum Type
	{
		Directional = 0,
		Point = 1,
		Spot = 2
	};

private:
	struct ShaderInput
	{
		DirectX::XMFLOAT4 position;
		DirectX::XMFLOAT4 direction;
		DirectX::XMFLOAT4 color;

		float spotAngle;
		float constantAttenuation;
		float linearAttenuation;
		float quadraticAttenuation;
		float intensity;
		int type;
		bool enabled;
		int padding;
	};

private:
	Type type;
	
	DirectX::XMFLOAT4 color;
	float spotAngle;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	float intensity;

	bool enabled;

public:
	Light();

	ShaderInput& GetShaderInput();
};