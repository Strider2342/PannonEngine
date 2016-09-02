#include "Script.h"

Script::Script()
{ }

bool Script::Load(std::string filename)
{
	return true;
}

void Script::SetFilename(std::string filename)
{
	this->filename = filename;
}