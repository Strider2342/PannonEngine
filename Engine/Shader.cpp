#include "Shader.h"

Shader::Shader()
{ }
Shader::~Shader()
{
	pLayout->Release();
	pVS->Release();
	pPS->Release();
}

void Shader::Init(ID3D11Device *dev, ID3D11DeviceContext *devcon)
{
	this->dev = dev;
	this->devcon = devcon;
}
void Shader::SetInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	HRESULT hr = dev->CreateInputLayout(ied, ARRAYSIZE(ied), VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
	
	if (hr != S_OK)
	{
		std::cout << "Input layout creation failed" << std::endl;
		return;
	}
	else
	{
		devcon->IASetInputLayout(pLayout);
	}
}
void Shader::SetInputLayoutQuad()
{
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	HRESULT hr = dev->CreateInputLayout(ied, ARRAYSIZE(ied), VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);

	if (hr != S_OK)
	{
		std::cout << "Input layout creation failed" << std::endl;
		return;
	}
	else
	{
		devcon->IASetInputLayout(pLayout);
	}
}
void Shader::LoadVertexShaderFromFile(LPCWSTR filename, std::string entrypoint)
{
	ID3DBlob *errorBlob = nullptr;
	
	HRESULT hr = D3DCompileFromFile(filename, nullptr, 0, entrypoint.c_str(), (dev->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "vs_5_0" : "vs_4_0", D3DCOMPILE_DEBUG, 0, &VS, &errorBlob);

	if (errorBlob)
	{
		OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		errorBlob->Release();
	}

	if (hr != S_OK)
	{
		std::cout << "Vertex shader failed to load" << std::endl;
		return;
	}
	else
	{
		//auto size = VS->GetBufferSize();
		//FILE *file = fopen("PhongVS.cso", "wb");
		//fwrite(VS->GetBufferPointer(), sizeof(char), size, file);
		//fclose(file);
		dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
	}

	SetInputLayout();
}
void Shader::LoadPixelShaderFromFile(LPCWSTR filename, std::string entrypoint)
{
	ID3DBlob *PS = nullptr;
	ID3DBlob *errorBlob = nullptr;

	HRESULT hr = D3DCompileFromFile(filename, nullptr, 0, entrypoint.c_str(), (dev->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "ps_5_0" : "ps_4_0", D3DCOMPILE_DEBUG, 0, &PS, &errorBlob);

	if (errorBlob)
	{
		OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		errorBlob->Release();
	}

	if (hr != S_OK)
	{
		std::cout << "Pixel shader failed to load" << std::endl;
		return;
	}
	else
	{
		//auto size = PS->GetBufferSize();
		//FILE *file = fopen("PhongPS.cso", "wb");
		//fwrite(PS->GetBufferPointer(), sizeof(char), size, file);
		//fclose(file);
		dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);
	}
}

void Shader::LoadVertexShaderPrecompiled(LPCWSTR filename)
{
	HRESULT hr = D3DReadFileToBlob(filename, &VS);
	if (hr != S_OK)
	{
		std::cout << "Vertex shader failed to load" << std::endl;
		return;
	}
	else
	{
		dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
	}

	SetInputLayout();
}

void Shader::LoadPixelShaderPrecompiled(LPCWSTR filename)
{
	ID3DBlob* PS;
	HRESULT hr = D3DReadFileToBlob(filename, &PS);
	if (hr != S_OK)
	{
		std::cout << "Pixel shader failed to load" << std::endl;
		return;
	}
	else
	{
		dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);
	}
}

ID3D11InputLayout* Shader::GetLayout()
{
	return pLayout;
}
ID3D11VertexShader* Shader::GetVertexShader()
{
	return pVS;
}
ID3D11PixelShader* Shader::GetPixelShader()
{
	return pPS;
}
