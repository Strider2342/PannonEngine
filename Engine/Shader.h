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

	ID3DBlob *VS = nullptr;
	ID3DBlob *PS = nullptr;

public:
	void SetInputLayout();
	void CreateVertexShader(std::string filename, std::string entrypoint);
	void CreatePixelShader(std::string filename, std::string entrypoint);

	void Clear();
};