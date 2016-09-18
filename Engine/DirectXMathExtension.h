#pragma once
#include <DirectXMath.h>

class DirectXExt
{
public:
	static void XMFloat3Normalize(DirectX::XMFLOAT3 *vector);
	static void XMFloat3CrossProduct(DirectX::XMFLOAT3 *dest, DirectX::XMFLOAT3 vec1, DirectX::XMFLOAT3 vec2);

	static void XMFloat3Add(DirectX::XMFLOAT3 *dest, DirectX::XMFLOAT3 vec1, DirectX::XMFLOAT3 vec2);
	static void XMFloat3Subtract(DirectX::XMFLOAT3 *dest, DirectX::XMFLOAT3 vec1, DirectX::XMFLOAT3 vec2);
	static void XMFloat3Multiply(DirectX::XMFLOAT3 *dest, float scalar);
};