#pragma once
#include <stdio.h>
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

	ID3DBlob *VS = nullptr;

public:
	Shader();
	~Shader();

	void Init(ID3D11Device *dev, ID3D11DeviceContext *devcon);
	void SetInputLayout();
	void SetInputLayoutQuad();
	void LoadVertexShaderFromFile(LPCWSTR filename, std::string entrypoint);
	void LoadPixelShaderFromFile(LPCWSTR filename, std::string entrypoint);
	void LoadVertexShaderPrecompiled(LPCWSTR filename);
	void LoadPixelShaderPrecompiled(LPCWSTR filename);

	ID3D11InputLayout* GetLayout();
	ID3D11VertexShader* GetVertexShader();
	ID3D11PixelShader* GetPixelShader();
};