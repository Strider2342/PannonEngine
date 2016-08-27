#pragma once
#include <d3d11.h>
#include <D3D11Shader.h>

class Shader
{
private:
	ID3D11InputLayout *pLayout = nullptr;

	ID3D11VertexShader *pVS = nullptr;
	ID3D11HullShader *pHS = nullptr;
	ID3D11DomainShader *pDS = nullptr;
	ID3D11GeometryShader *pGS = nullptr;
	ID3D11PixelShader *pPS = nullptr;
};