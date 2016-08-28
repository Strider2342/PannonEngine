#include "Texture.h"

Texture::Texture()
{ }

Texture::~Texture()
{
	Destroy();
}

ID3D11ShaderResourceView* Texture::GetTexture()
{
	return texture_resource;
}

void Texture::SetTexture(ID3D11ShaderResourceView *texture_resource)
{
	this->texture_resource = texture_resource;
}

void Texture::Destroy()
{
	if (texture_resource != nullptr)
	{
		texture_resource->Release();
	}
}