#pragma once
#include <iostream>
#include "EditorGraphics.h"
#include "Editor.h"
#include "Scene1.h"

class Application
{
private:
	HWND hWnd;
	EditorGraphics graphics;

	Editor editor;

	Scene1 scene1;

public:
	Application();
	Application(HWND &hWnd);

	void Run();
};