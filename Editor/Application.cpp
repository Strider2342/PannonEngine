#include "Application.h"

Application::Application()
{
	graphics = Graphics();
}

void Application::Run()
{
	graphics.Init();
	MSG msg;

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
	}
}