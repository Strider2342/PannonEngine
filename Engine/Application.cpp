#include "Application.h"

Application::Application()
{
	graphics = Graphics();

	scenes = std::vector<Scene *>();
}

Application::Application(HWND& hWnd)
{
	graphics = Graphics();
	graphics.Init(hWnd);

	scenes = std::vector<Scene *>();
}

void Application::Run()
{
	MSG msg;

	GameScene *scene = dynamic_cast<GameScene *>(scenes[currentScene]);

	scene->Init(graphics);
	scene->Start();
	
	std::cout << "Application started" << std::endl;

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

		//scene->Export();
	}

	graphics.CleanD3D();
}

void Application::SetType(ApplicationType type)
{
	this->type = type;
}