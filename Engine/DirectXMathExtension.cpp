#include "DirectXMathExtension.h"

void DirectXExt::XMFloat3Normalize(DirectX::XMFLOAT3 *vector)
{
	DirectX::XMStoreFloat3(vector, DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(vector)));
}
void DirectXExt::XMFloat3CrossProduct(DirectX::XMFLOAT3 *dest, DirectX::XMFLOAT3 vec1, DirectX::XMFLOAT3 vec2)
{
	DirectX::XMStoreFloat3(dest, DirectX::XMVector3Cross(DirectX::XMLoadFloat3(&vec1), DirectX::XMLoadFloat3(&vec2)));
}

void DirectXExt::XMFloat3Add(DirectX::XMFLOAT3 *dest, DirectX::XMFLOAT3 vec1, DirectX::XMFLOAT3 vec2)
{
	dest->x = vec1.x + vec2.x;
	dest->y = vec1.y + vec2.y;
	dest->z = vec1.z + vec2.z;
}
void DirectXExt::XMFloat3Subtract(DirectX::XMFLOAT3 *dest, DirectX::XMFLOAT3 vec1, DirectX::XMFLOAT3 vec2)
{
	dest->x = vec1.x - vec2.x;
	dest->y = vec1.y - vec2.y;
	dest->z = vec1.z - vec2.z;
}
void DirectXExt::XMFloat3Multiply(DirectX::XMFLOAT3 *dest, float scalar)
{
	dest->x *= scalar;
	dest->y *= scalar;
	dest->z *= scalar;
}
