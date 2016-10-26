#include "Triangle.h"

Triangle::Triangle()
{
	pointA = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	pointB = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	pointC = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
}

Triangle::Triangle(DirectX::XMFLOAT3 pointA, DirectX::XMFLOAT3 pointB, DirectX::XMFLOAT3 pointC)
{
	this->pointA = pointA;
	this->pointB = pointB;
	this->pointC = pointC;
}

DirectX::XMFLOAT3& Triangle::GetPointA()
{
	return pointA;
}

DirectX::XMFLOAT3& Triangle::GetPointB()
{
	return pointB;
}

DirectX::XMFLOAT3& Triangle::GetPointC()
{
	return pointC;
}
