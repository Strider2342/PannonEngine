#pragma once
#include <iostream>
#include <string>
#include <DirectXMath.h>

class Vector3
{
private:
	float X;
	float Y;
	float Z;

public:
	Vector3();
	Vector3(int X, int Y, int Z);
	Vector3(float X, float Y, float Z);
	Vector3(const Vector3 &vector);

	void SetX(int value);
	void SetX(float value);
	void SetY(int value);
	void SetY(float value);
	void SetZ(int value);
	void SetZ(float value);

	void Normalize();

	float GetX() const;
	float GetY() const;
	float GetZ() const;

	float GetLength() const;

	std::string ToString();
	DirectX::XMVECTOR ToXMVector();
	
	static Vector3& Normalize(Vector3 vector);
	static Vector3& TransformByMatrix(Vector3 vector, DirectX::XMMATRIX &matrix);
};