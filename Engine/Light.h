#pragma once
#include "Vector3.h"

class GameObject;
class Transform;
class Light
{
public:
	static enum Type
	{
		Directional,
		Point,
		Spot
	};

private:
	GameObject *gameObject = nullptr;
	Transform *transform = nullptr;

	Type type;

	Vector3 color;
	float spotAngle;
	float attenuation;
	float intensity;

public:
	Light();
};