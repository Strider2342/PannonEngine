#include "Light.h"

Light::Light()
{
	color = DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	spotAngle = 0.05f;
	constantAttenuation = 0.25f;
	linearAttenuation = 0.25f;
	quadraticAttenuation = 0.25f;
	intensity = 0.75f;
	type = Type::Point;

	enabled = true;
}

Light::ShaderInput& Light::GetShaderInput()
{
	ShaderInput shaderInput;

	shaderInput.position = DirectX::XMFLOAT4(transform->GetPosition().x, transform->GetPosition().y, transform->GetPosition().z, 1.0f);
	shaderInput.direction = DirectX::XMFLOAT4(transform->GetForward().x, transform->GetForward().y, transform->GetForward().z, 1.0f);
	shaderInput.color = color; // DirectX::XMFLOAT4(color.x * intensity, color.y * intensity, color.z * intensity, 1.0f);
	shaderInput.spotAngle = spotAngle;
	shaderInput.constantAttenuation = constantAttenuation;
	shaderInput.linearAttenuation = linearAttenuation;
	shaderInput.quadraticAttenuation = quadraticAttenuation;
	shaderInput.intensity = intensity;
	shaderInput.type = type;
	shaderInput.enabled = enabled;

	return shaderInput;
}

Transform* Light::GetTransform()
{
	return transform;
}

bool Light::GetEnabled()
{
	return enabled;
}
int Light::GetType()
{
	return type;
}
float Light::GetIntensity()
{
	return intensity;
}
float Light::GetConstantAttenuation()
{
	return constantAttenuation;
}
float Light::GetLinearAttenuation()
{
	return linearAttenuation;
}
float Light::GetQuadraticAttenuation()
{
	return quadraticAttenuation;
}
float Light::GetSpotAngle()
{
	return spotAngle;
}

DirectX::XMFLOAT4& Light::GetColor()
{
	return color;
}

void Light::SetEnabled(bool enabled)
{
	this->enabled = enabled;
}
void Light::SetType(int type)
{
	this->type = static_cast<Type>(type);
}
void Light::SetIntensity(float intensity)
{
	this->intensity = intensity;
}
void Light::SetConstantAttenuation(float constantAttenuation)
{
	this->constantAttenuation = constantAttenuation;
}
void Light::SetLinearAttenuation(float linearAttenuation)
{
	this->linearAttenuation = linearAttenuation;
}
void Light::SetQuadraticAttenuation(float quadraticAttenuation)
{
	this->quadraticAttenuation = quadraticAttenuation;
}
void Light::SetSpotAngle(float spotAngle)
{
	this->spotAngle = spotAngle;
}

void Light::SetColor(DirectX::XMFLOAT4 color)
{
	this->color = color;
}

void Light::Start()
{
	transform = gameObject->GetTransform();
}