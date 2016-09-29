#pragma once
#include <DirectXMath.h>
#include "GameObject.h"
#include "Component.h"

class Light : public Component
{
public:
	static enum Type
	{
		Directional = 0,
		Point = 1,
		Spot = 2
	};

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
	Transform *transform;

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

	// get
	ShaderInput& GetShaderInput();
	Transform *GetTransform();
	float &GetIntensity();

	// set
	void SetTransform(Transform *transform);
};