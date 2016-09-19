#pragma once
#include <iostream>
#include <d3d11.h>
#include "Transform.h"

class Object
{
protected:
	ID3D11Device *dev = nullptr;
	ID3D11DeviceContext *devcon = nullptr;

	Transform *transform = nullptr;

	std::string name;

public:
	Object();
	~Object();

	Transform* GetTransform();

	void SetTransform(Transform *transform);
};