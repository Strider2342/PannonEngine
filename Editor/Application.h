#pragma once
#include <iostream>
#include "Graphics.h"
#include "Scene.h"

class Application
{
private:
	Graphics graphics;

	Scene scene;

public:
	Application();

	void Run();
};