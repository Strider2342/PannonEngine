#pragma once
#include <iostream>
#include <string>

class Object
{
protected:

public:
	Object();

	virtual std::string Export();
	virtual void Import(std::string json);
};