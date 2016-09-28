#include "Application.h"

Application::Application()
{ }

Application::Application(HWND &hWnd)
{
	this->hWnd = hWnd;
	graphics = EditorGraphics();
}

void Application::Run()
{
	graphics.Init(hWnd);
	MSG msg;

	editor.Init(&graphics);
	editor.Load();

	std::cout << "Application started";

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			editor.Update();
			editor.Draw();
		}
	}

	ImGui_ImplDX11_Shutdown();

	graphics.CleanD3D();
}