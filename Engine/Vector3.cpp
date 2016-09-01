#include "Vector3.h"

Vector3::Vector3()
{
	this->X = 0.0f;
	this->Y = 0.0f;
	this->Z = 0.0f;
}
Vector3::Vector3(int X, int Y, int Z)
{
	this->X = X;
	this->Y = Y;
	this->Z = Z;
}
Vector3::Vector3(const Vector3 &vector)
{
	this->X = vector.X;
	this->Y = vector.Y;
	this->Z = vector.Z;
}

void Vector3::SetX(int value)
{
	X = value;
}
void Vector3::SetX(float value)
{
	X = value;
}
void Vector3::SetY(int value)
{
	Y = value;
}
void Vector3::SetY(float value)
{
	Y = value;
}
void Vector3::SetZ(int value)
{
	Z = value;
}
void Vector3::SetZ(float value)
{
	Z = value;
}

float Vector3::GetX() const
{
	return X;
}
float Vector3::GetY() const
{
	return Y;
}
float Vector3::GetZ() const
{
	return Z;
}
float Vector3::GetLength() const
{
	return sqrt(X*X + Y*Y + Z*Z);
}

std::string Vector3::ToString()
{
	return "{" + std::to_string(X) + "; " + std::to_string(Y) + "; " + std::to_string(Z) + "}";
}