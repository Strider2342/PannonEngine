#pragma once
#include <DirectXMath.h>
#include "GameObject.h"
#include "Component.h"

class Light : public Component
{
public:
	static enum Type
	{
		Directional,
		Point,
		Spot
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
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	float spotAngle;
	float intensity;

	bool enabled;

public:
	Light();

	// get
	ShaderInput& GetShaderInput();
	Transform* GetTransform();

	bool GetEnabled();

	int GetType();

	float GetIntensity();
	float GetConstantAttenuation();
	float GetLinearAttenuation();
	float GetQuadraticAttenuation();
	float GetSpotAngle();

	DirectX::XMFLOAT4& GetColor();

	// set
	void SetEnabled(bool enadbled);

	void SetType(int type);

	void SetIntensity(float intensity);
	void SetConstantAttenuation(float constantAttenuation);
	void SetLinearAttenuation(float linearAttenuation);
	void SetQuadraticAttenuation(float quadraticAttenuation);
	void SetSpotAngle(float spotAngle);

	void SetColor(DirectX::XMFLOAT4 color);

	void Start();

	// object
	std::string Export();
	void Import(std::string json);
};