#include "ContentManager.h"

ContentManager::ContentManager()
{ }

void ContentManager::Init(ID3D11Device* dev, ID3D11DeviceContext* devcon)
{
	this->dev = dev;
	this->devcon = devcon;

	resourceDir = "../";
}

Texture* ContentManager::LoadTexture(std::string filename)
{
	ID3D11ShaderResourceView *texture_resource;
	int width, height, n;

	std::string path = resourceDir + "Textures/" + filename;
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &n, 0);

	if (data == nullptr)
	{
		std::cout << "Unable to load texture " + path << std::endl;
		return nullptr;
	}

	D3D11_TEXTURE2D_DESC desc = D3D11_TEXTURE2D_DESC();
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = desc.ArraySize = 1;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

	ID3D11Texture2D *pTexture = NULL;
	D3D11_SUBRESOURCE_DATA subdata = D3D11_SUBRESOURCE_DATA();
	subdata.pSysMem = data;
	subdata.SysMemPitch = width * n;
	subdata.SysMemSlicePitch = 0;
	HRESULT hr = dev->CreateTexture2D(&desc, &subdata, &pTexture);

	D3D11_SHADER_RESOURCE_VIEW_DESC resDesc = D3D11_SHADER_RESOURCE_VIEW_DESC();
	resDesc.Format = desc.Format;
	resDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	resDesc.Texture2D.MostDetailedMip = 0;
	resDesc.Texture2D.MipLevels = 1;
	hr = dev->CreateShaderResourceView(pTexture, &resDesc, &texture_resource);

	pTexture->Release();
	stbi_image_free(data);

	Texture *texture = new Texture();
	texture->SetTexture(texture_resource);

	texture->SetPath(filename);

	return texture;
}

Material* ContentManager::LoadMaterial(std::string filename)
{
	Material *newmaterial = new Material();

	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(resourceDir + filename, aiProcessPreset_TargetRealtime_Fast);

	aiMaterial *material = scene->mMaterials[0];
	aiColor3D diffuse;
	aiColor3D specular;
	aiColor3D ambient;
	aiColor3D emissive;

	material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
	material->Get(AI_MATKEY_COLOR_SPECULAR, specular);
	material->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
	material->Get(AI_MATKEY_COLOR_EMISSIVE, emissive);

	newmaterial->SetDiffuse(diffuse.r, diffuse.g, diffuse.b);
	newmaterial->SetSpecular(specular.r, specular.g, specular.b);
	newmaterial->SetAmbient(ambient.r, ambient.g, ambient.b);
	newmaterial->SetEmissive(emissive.r, emissive.g, emissive.b);

	return newmaterial;
}

Mesh* ContentManager::LoadMesh(std::string filename)
{
	Mesh *newmesh = new Mesh();

	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(resourceDir + filename, aiProcessPreset_TargetRealtime_Fast);

	aiMesh *mesh = scene->mMeshes[0];

	std::vector<Vertex> vertices;
	std::vector<DWORD> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.position = DirectX::XMFLOAT3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.normal = DirectX::XMFLOAT3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		vertex.uv = DirectX::XMFLOAT2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

		vertices.push_back(vertex);
	}
	
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		const aiFace face = mesh->mFaces[i];

		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}

	newmesh->SetVertices(vertices);
	newmesh->SetIndices(indices);

	newmesh->SetBounds();

	newmesh->SetPath(filename);

	return newmesh;
}