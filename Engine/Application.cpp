#include "Application.h"

Application::Application()
{
	graphics = Graphics();
}

void Application::Run()
{
	graphics.Init();
	MSG msg;

	scenes[currentScene]->Init(graphics);
	scenes[currentScene]->Start();
	scenes[currentScene]->Load();

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

		scenes[currentScene]->PreUpdate();
		scenes[currentScene]->Update();
		scenes[currentScene]->PostUpdate();

		scenes[currentScene]->Render();
		scenes[currentScene]->PostRender();
	}

	graphics.CleanD3D();
}