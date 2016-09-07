#pragma once
#include <iostream>
#include <d3d11.h>
#include "Transform.h"
#include "Script.h"

class Object
{
protected:
	ID3D11Device *dev = nullptr;
	ID3D11DeviceContext *devcon = nullptr;

	Transform *transform = nullptr;
	Script *script = nullptr;

	std::string name;

public:
	Object();
	~Object();

	Transform* GetTransform();
	Script* GetScript();

	void SetTransform(Transform *transform);
	void SetScript(Script *script);
};