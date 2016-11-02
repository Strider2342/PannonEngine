#include "Material.h"

Material::Material()
{ }

Material::~Material()
{
	/*delete texture;
	delete shader;

	texture = nullptr;
	shader = nullptr;*/
}

void Material::Init(ID3D11Device *dev, ID3D11DeviceContext *devcon)
{
	shader = new Shader();
	shader->Init(dev, devcon);

	diffuse = DirectX::XMFLOAT3(0.8f, 0.8f, 0.8f);
	specular = DirectX::XMFLOAT3(0.774597f, 0.774597f, 0.774597f);
	ambient = DirectX::XMFLOAT3(0.25f, 0.25f, 0.25f);
	emissive = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

	power = 78.6f;

	hasTexture = false;
	useTexture = false;
}

ID3D11ShaderResourceView* Material::GetTextureResource()
{
	return texture->GetTexture();
}

Texture& Material::GetTexture()
{
	return *texture;
}

Shader& Material::GetShader()
{
	return *shader;
}

DirectX::XMFLOAT3 Material::GetDiffuse()
{
	return diffuse;
}

DirectX::XMFLOAT3 Material::GetSpecular()
{
	return specular;
}

DirectX::XMFLOAT3 Material::GetAmbient()
{
	return ambient;
}

DirectX::XMFLOAT3 Material::GetEmissive()
{
	return emissive;
}

float Material::GetPower()
{
	return power;
}

bool Material::HasTexture()
{
	return hasTexture;
}

bool Material::GetUseTexture()
{
	return useTexture;
}

Material::ShaderInput& Material::GetShaderInput()
{
	ShaderInput shaderInput;

	shaderInput.diffuse = DirectX::XMFLOAT4(diffuse.x, diffuse.y, diffuse.z, 1.0f);
	shaderInput.specular = DirectX::XMFLOAT4(specular.x, specular.y, specular.z, 1.0f);
	shaderInput.ambient = DirectX::XMFLOAT4(ambient.x, ambient.y, ambient.z, 1.0f);
	shaderInput.emissive = DirectX::XMFLOAT4(emissive.x, emissive.y, emissive.z, 1.0f);
	shaderInput.power = power;
	shaderInput.useTexture = useTexture;

	return shaderInput;
}

void Material::SetTexture(Texture *texture)
{
	this->texture = texture;
	hasTexture = true;
}

void Material::SetShader(Shader *shader)
{
	this->shader = shader;
}

void Material::SetDiffuse(float r, float g, float b)
{
	diffuse = DirectX::XMFLOAT3(r, g, b);
}

void Material::SetSpecular(float r, float g, float b)
{
	specular = DirectX::XMFLOAT3(r, g, b);
}

void Material::SetAmbient(float r, float g, float b)
{
	ambient = DirectX::XMFLOAT3(r, g, b);
}

void Material::SetEmissive(float r, float g, float b)
{
	emissive = DirectX::XMFLOAT3(r, g, b);
}

void Material::SetPower(float value)
{
	power = value;
}

void Material::SetUseTexture(bool value)
{
	useTexture = value;
}