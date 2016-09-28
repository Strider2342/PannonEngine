#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "EditorWindow.h"
#include "Application.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	ImGui_ImplDX11_WndProcHandler(hWnd, message, wParam, lParam);

	switch (message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

int main()
{
	EditorWindow window = EditorWindow(1706, 960, L"PannonEditor", L"WindowClass", WindowProc);

	Application application = Application(window.GetHWND());

	application.Run();

	return 0;
}