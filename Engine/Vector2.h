#pragma once
#include <iostream>
#include <string>

class Vector2
{
private:
	float X;
	float Y;

public:
	Vector2();
	Vector2(int X, int Y);
	Vector2(float X, float Y);
	Vector2(const Vector2 &vector);

	void SetX(int value);
	void SetX(float value);
	void SetY(int value);
	void SetY(float value);

	float GetX() const;
	float GetY() const;

	float GetLength() const;

	std::string ToString();
};