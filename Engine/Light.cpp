#include "Light.h"

Light::Light()
{
	color = DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	spotAngle = 5.0f;
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

std::string Light::Export()
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);

	writer.StartObject();
	writer.Key("light");
	writer.StartObject();
	writer.Key("type");
	writer.Int(type);
	writer.Key("color");
	writer.StartObject();
	writer.Key("x");
	writer.Double(color.x);
	writer.Key("y");
	writer.Double(color.y);
	writer.Key("z");
	writer.Double(color.z);
	writer.EndObject();
	writer.Key("spotAngle");
	writer.Double(spotAngle);
	writer.Key("constantAttenuation");
	writer.Double(constantAttenuation);
	writer.Key("linearAttenuation");
	writer.Double(linearAttenuation);
	writer.Key("quadraticAttenuation");
	writer.Double(quadraticAttenuation);
	writer.Key("intensity");
	writer.Double(intensity);
	writer.Key("enabled");
	writer.Bool(enabled);
	writer.EndObject();
	writer.EndObject();

	return s.GetString();
}

void Light::Import(std::string json)
{
	Document d;
	d.Parse(json.c_str());

	float color_x = d["color"]["x"].GetFloat();
	float color_y = d["color"]["y"].GetFloat();
	float color_z = d["color"]["z"].GetFloat();
	color = DirectX::XMFLOAT4(color_x, color_y, color_z, 1.0f);

	spotAngle				= d["light"]["spotAngle"].GetFloat();
	constantAttenuation		= d["light"]["constantAttenuation"].GetFloat();
	linearAttenuation		= d["light"]["linearAttenuation"].GetFloat();
	quadraticAttenuation	= d["light"]["quadraticAttenuation"].GetFloat();
	intensity				= d["light"]["intensity"].GetFloat();
	enabled					= d["light"]["enabled"].GetBool();
}
