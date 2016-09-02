#pragma once
#include <iostream>
#include "Transform.h"
#include "Script.h"

class Object
{
protected:
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