#include "Application.h"

Application::Application()
{
	graphics = Graphics();
}

Application::Application(HWND& hWnd)
{
	graphics = Graphics();
	graphics.Init(hWnd);
}

void Application::Run()
{
	MSG msg;

	GameScene *scene = dynamic_cast<GameScene *>(scenes[currentScene]);

	scene->Init(graphics);
	scene->Start();

	std::cout << "Application started";

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_SIZE)
				graphics.Resize();

			if (msg.message == WM_QUIT)
				break;
		}

		scene->PreUpdate();
		scene->Update();
		scene->PostUpdate();

		scene->Render();
		scene->PostRender();
	}

	graphics.CleanD3D();
}

void Application::SetType(ApplicationType type)
{
	this->type = type;
}