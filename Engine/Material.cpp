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

std::string Material::Export()
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);

	writer.StartObject();
	writer.Key("material");
	writer.StartObject();
	writer.Key("diffuse");
	writer.StartObject();
	writer.Key("x");
	writer.Double(diffuse.x);
	writer.Key("y");
	writer.Double(diffuse.y);
	writer.Key("z");
	writer.Double(diffuse.z);
	writer.EndObject();
	writer.Key("specular");
	writer.StartObject();
	writer.Key("x");
	writer.Double(specular.x);
	writer.Key("y");
	writer.Double(specular.y);
	writer.Key("z");
	writer.Double(specular.z);
	writer.EndObject();
	writer.Key("ambient");
	writer.StartObject();
	writer.Key("x");
	writer.Double(ambient.x);
	writer.Key("y");
	writer.Double(ambient.y);
	writer.Key("z");
	writer.Double(ambient.z);
	writer.EndObject();
	writer.Key("power");
	writer.Double(power);
	writer.Key("hasTexture");
	writer.Bool(hasTexture);
	writer.Key("useTexture");
	writer.Bool(useTexture);
	writer.EndObject();
	writer.EndObject();

	std::string str = s.GetString();

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '\"')
		{
			str[i] = '\'';
		}
	}

	return str;
}

void Material::Import(const Value &component)
{
	float diffuse_x = component["diffuse"]["x"].GetFloat();
	float diffuse_y = component["diffuse"]["y"].GetFloat();
	float diffuse_z = component["diffuse"]["x"].GetFloat();

	float specular_x = component["specular"]["x"].GetFloat();
	float specular_y = component["specular"]["y"].GetFloat();
	float specular_z = component["specular"]["x"].GetFloat();

	float ambient_x = component["ambient"]["x"].GetFloat();
	float ambient_y = component["ambient"]["y"].GetFloat();
	float ambient_z = component["ambient"]["x"].GetFloat();

	float emissive_x = component["emissive"]["x"].GetFloat();
	float emissive_y = component["emissive"]["y"].GetFloat();
	float emissive_z = component["emissive"]["x"].GetFloat();

	diffuse = DirectX::XMFLOAT3(diffuse_x, diffuse_y, diffuse_z);
	specular = DirectX::XMFLOAT3(specular_x, specular_y, specular_z);
	ambient = DirectX::XMFLOAT3(ambient_x, ambient_y, ambient_z);
	emissive = DirectX::XMFLOAT3(emissive_x, emissive_y, emissive_z);
}
