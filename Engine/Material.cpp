#include "Material.h"

Material::Material()
{ }

Material::Material(ID3D11Device *dev, ID3D11DeviceContext *devcon)
{
	shader = new Shader();
	shader->Init(dev, devcon);

	shader->CreateVertexShader("Shaders/DefShader.hlsl", "VSMain");
	shader->CreatePixelShader("Shaders/DefShader.hlsl", "PSMain");
}

Material::~Material()
{
	/*delete texture;
	delete shader;

	texture = nullptr;
	shader = nullptr;*/
}

ID3D11ShaderResourceView* Material::GetTexture()
{
	return texture->GetTexture();
}

void Material::SetTexture(Texture *texture)
{
	this->texture = texture;
}

void Material::SetShader(Shader *shader)
{
	this->shader = shader;
}