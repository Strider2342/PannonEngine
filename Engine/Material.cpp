#include "Material.h"

Material::Material()
{ }

void Material::Init(ID3D11Device *dev, ID3D11DeviceContext *devcon)
{
	shader = new Shader();
	shader->Init(dev, devcon);

	shader->CreateVertexShader("Shaders/DefShader.hlsl", "VShader");
	shader->CreatePixelShader("Shaders/DefShader.hlsl", "PShader");
}

Material::~Material()
{
	/*delete texture;
	delete shader;

	texture = nullptr;
	shader = nullptr;*/
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

void Material::SetTexture(Texture *texture)
{
	this->texture = texture;
}

void Material::SetShader(Shader *shader)
{
	this->shader = shader;
}