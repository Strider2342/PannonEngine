#include "Vector2.h"

Vector2::Vector2()
{
	this->X = 0.0f;
	this->Y = 0.0f;
}
Vector2::Vector2(int X, int Y)
{
	this->X = X;
	this->Y = Y;
}
Vector2::Vector2(const Vector2 &vector)
{
	this->X = vector.X;
	this->Y = vector.Y;
}

void Vector2::SetX(int value)
{
	X = value;
}
void Vector2::SetX(float value)
{
	X = value;
}
void Vector2::SetY(int value)
{
	Y = value;
}
void Vector2::SetY(float value)
{
	Y = value;
}

float Vector2::GetX() const
{
	return X;
}
float Vector2::GetY() const
{
	return Y;
}
float Vector2::GetLength() const
{
	return sqrt(X*X + Y*Y);
}

std::string Vector2::ToString()
{
	return "{" + std::to_string(X) + "; " + std::to_string(Y) + "}";
}