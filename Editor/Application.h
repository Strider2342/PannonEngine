#pragma once
#include <iostream>
#include "EditorGraphics.h"
#include "Editor.h"

class Application
{
private:
	EditorGraphics graphics;

	Editor editor;

public:
	Application();

	void Run();
};