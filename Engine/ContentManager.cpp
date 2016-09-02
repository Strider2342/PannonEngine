#include "ContentManager.h"

ContentManager::ContentManager()
{ }

void ContentManager::Init(ID3D11Device* dev, ID3D11DeviceContext* devcon)
{
	this->dev = dev;
	this->devcon = devcon;
}

Texture* ContentManager::LoadTexture(std::string filename)
{
	ID3D11ShaderResourceView *texture_resource;
	int x, y, n;

	std::string path = "Textures/" + filename;
	unsigned char *data = stbi_load(path.c_str(), &x, &y, &n, 0);

	if (data == nullptr) {
		throw std::runtime_error("Unable to load texture file: " + path);
	}
	
	D3D11_TEXTURE2D_DESC desc = D3D11_TEXTURE2D_DESC();
	desc.Width = x;
	desc.Height = y;
	desc.MipLevels = desc.ArraySize = 1;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	switch (n)
	{
	case 1:
	{
		desc.Format = DXGI_FORMAT_R8_UNORM;
		break;
	}
	case 2:
	{
		desc.Format = DXGI_FORMAT_R8G8_UNORM;
		break;
	}
	case 3:
	{
		UINT* newdata = new UINT[x*y];
		UCHAR* dst = (UCHAR*)newdata;
		UCHAR* src = (UCHAR*)data;
		size_t wx = x;
		size_t wy = y;
		size_t stride_src = wx * 3;
		size_t stride_dst = wx * 4;
		while (wy--) {
			while (wx--) {
				dst[4 * wx + 0] = src[3 * wx + 0];
				dst[4 * wx + 1] = src[3 * wx + 1];
				dst[4 * wx + 2] = src[3 * wx + 2];
				dst[4 * wx + 3] = 0xff;
			}
			src += stride_src;
			dst += stride_dst;
			wx = x;
		}
		n = 4;
		delete data;
		data = (UCHAR*)newdata;

		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	} break;

	case 4:
	{
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		break;
	}
	}

	ID3D11Texture2D *pTexture = NULL;
	D3D11_SUBRESOURCE_DATA subdata = D3D11_SUBRESOURCE_DATA();
	subdata.pSysMem = data;
	subdata.SysMemPitch = x * n;
	subdata.SysMemSlicePitch = 0;
	HRESULT hr = dev->CreateTexture2D(&desc, &subdata, &pTexture);

	D3D11_SHADER_RESOURCE_VIEW_DESC resDesc = D3D11_SHADER_RESOURCE_VIEW_DESC();
	resDesc.Format = desc.Format;
	resDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	resDesc.Texture2D.MostDetailedMip = 0;
	resDesc.Texture2D.MipLevels = 1;
	hr = dev->CreateShaderResourceView(pTexture, &resDesc, &texture_resource);

	pTexture->Release();
	delete data;

	Texture *texture = new Texture();
	texture->SetTexture(texture_resource);

	return texture;
}

Mesh* ContentManager::LoadMesh(std::string filename)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(filename, aiProcessPreset_TargetRealtime_Fast);

	aiMesh *mesh = scene->mMeshes[0];

	aiMaterial *material = scene->mMaterials[0];
	aiColor3D diffuse;
	aiColor3D specular;
	aiColor3D ambient;
	aiColor3D emissive;

	return nullptr;
}
