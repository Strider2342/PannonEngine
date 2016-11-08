#pragma once
#include <iostream>
#include <vector>

static bool GetFileList(std::string cmd, std::vector<std::string> *directories)
{
	FILE *in;
	char buff[1024];

	if (!(in = _popen(cmd.c_str(), "r")))
	{
		return false;
	}

	while (fgets(buff, sizeof(buff), in) != NULL)
	{
		directories->push_back(buff);
		directories->at(directories->size() - 1).erase(directories->at(directories->size() - 1).size() - 1);
	}
	_pclose(in);

	return true;
}