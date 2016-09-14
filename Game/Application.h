#pragma once
#include <iostream>
#include "Graphics.h"
#include "Scene1.h"

class Application
{
private:
	Graphics graphics;

	Scene1 scene;

public:
	Application();

	void Run();
};