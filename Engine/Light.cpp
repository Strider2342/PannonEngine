#include "Light.h"

Light::Light()
{
	color = DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	spotAngle = 45.0f;
	constantAttenuation = 0.25f;
	linearAttenuation = 0.25f;
	quadraticAttenuation = 0.25f;
	float intensity = 0.75f;
	int type = Type::Point;

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
	shaderInput.type = 1;//(int)type;
	shaderInput.enabled = enabled;

	return shaderInput;
}

Transform* Light::GetTransform()
{
	return transform;
}

float& Light::GetIntensity()
{
	return intensity;
}

void Light::SetTransform(Transform *transform)
{
	this->transform = transform;
}
