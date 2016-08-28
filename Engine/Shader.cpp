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
	dev->CreateInputLayout(ied, ARRAYSIZE(ied), VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
	devcon->IASetInputLayout(pLayout);
}

void Shader::CreateVertexShader(std::string filename, std::string entrypoint)
{
	ID3DBlob *errorBlob = nullptr;
	
	HRESULT hr = D3DCompileFromFile((LPCWSTR)filename.c_str(), nullptr, 0, entrypoint.c_str(), (dev->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "vs_5_0" : "vs_4_0", D3DCOMPILE_DEBUG, 0, &VS, &errorBlob);

	if (errorBlob)
	{
		OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		errorBlob->Release();
	}

	if (hr != S_OK)
	{
		return;
	}
	else
	{
		dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
	}
}

void Shader::CreatePixelShader(std::string filename, std::string entrypoint)
{
	ID3DBlob *errorBlob = nullptr;

	HRESULT hr = D3DCompileFromFile((LPCWSTR)filename.c_str(), nullptr, 0, entrypoint.c_str(), (dev->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "vs_5_0" : "vs_4_0", D3DCOMPILE_DEBUG, 0, &PS, &errorBlob);

	if (errorBlob)
	{
		OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		errorBlob->Release();
	}

	if (hr != S_OK)
	{
		return;
	}
	else
	{
		dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);
	}
}