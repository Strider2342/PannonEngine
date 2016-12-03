#include "Application.h"

Application::Application()
{
	graphics = Graphics();

	builder = GameBuilder();

	scenes = std::vector<Scene *>();
}

Application::Application(HWND& hWnd)
{
	graphics = Graphics();
	graphics.Init(hWnd);

	builder = GameBuilder();
	builder.SetProjectPath(projectPath);

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

std::string Application::GetProjectPath()
{
	return projectPath;
}

void Application::SetProjectPath(std::string projectPath)
{
	this->projectPath = projectPath;
}
