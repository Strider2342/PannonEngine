#pragma once
#include <iostream>
#include <d3d11.h>
#include <D3D11Shader.h>
#include <D3Dcompiler.h>

class Shader
{
private:
	ID3D11Device *dev;
	ID3D11DeviceContext *devcon;

	ID3D11InputLayout *pLayout = nullptr;

	ID3D11VertexShader *pVS = nullptr;
	ID3D11HullShader *pHS = nullptr;
	ID3D11DomainShader *pDS = nullptr;
	ID3D11GeometryShader *pGS = nullptr;
	ID3D11PixelShader *pPS = nullptr;

public:
	Shader();
	~Shader();

	void Init(ID3D11Device *dev, ID3D11DeviceContext *devcon);
	void SetInputLayout(ID3DBlob *VS);
	void CreateVertexShader(LPCWSTR filename, std::string entrypoint);
	void CreatePixelShader(LPCWSTR filename, std::string entrypoint);

	ID3D11InputLayout* GetLayout();
	ID3D11VertexShader* GetVertexShader();
	ID3D11PixelShader* GetPixelShader();
};