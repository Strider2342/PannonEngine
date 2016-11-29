#pragma once
#include <iostream>
#include <string>
#include "GameTime.h"
#include "Component.h"
#include "Input.h"

class ScriptComponent : public Component
{

public:
	ScriptComponent() {}
	virtual std::string ScriptName() = 0;
};

template <class T>
class Script : public ScriptComponent
{
protected:
	std::string classname;

public:
	std::string ScriptName();
};

template<class T>
inline std::string Script<T>::ScriptName()
{
	std::string name = typeid(T).name();
	return name.substr(6, name.size() - 6);
}
