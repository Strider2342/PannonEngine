#include "Light.h"

Light::Light()
{
	color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	spotAngle = 45.0f;

	enabled = true;
}

Light::ShaderInput& Light::GetShaderInput()
{
	ShaderInput shaderInput;

	shaderInput.position = DirectX::XMFLOAT4(transform->GetPosition().x, transform->GetPosition().y, transform->GetPosition().z, 1.0f);
	shaderInput.direction = DirectX::XMFLOAT4(transform->GetForward().x, transform->GetForward().y, transform->GetForward().z, 1.0f);
	shaderInput.color = color;
	shaderInput.spotAngle = spotAngle;
	shaderInput.constantAttenuation = constantAttenuation;
	shaderInput.linearAttenuation = linearAttenuation;
	shaderInput.quadraticAttenuation = quadraticAttenuation;
	shaderInput.intensity = intensity;
	shaderInput.type = (int)type;
	shaderInput.enabled = enabled;

	return shaderInput;
}