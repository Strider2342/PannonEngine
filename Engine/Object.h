#pragma once
#include <iostream>
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

class Object
{
protected:

public:
	Object();

	virtual std::string Export();
	virtual void Import(const Value &component);
};