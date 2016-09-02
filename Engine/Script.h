#pragma once
#include <iostream>

class Script
{
private:
	std::string filename;
	std::string source;

public:
	Script();

	bool Load(std::string filename);
	
	void SetFilename(std::string filename);
};