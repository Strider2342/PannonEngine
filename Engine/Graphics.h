#pragma once
#include "GraphicsOptions.h"
#include "GameWindow.h"

class Graphics
{
private:
	GraphicsOptions options;
	GameWindow window;

public:
	Graphics();

	void Init();
};