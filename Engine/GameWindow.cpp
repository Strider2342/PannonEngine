#include "GameWindow.h"

GameWindow::GameWindow()
{ }

GameWindow::GameWindow(int SCREEN_WIDTH, int SCREEN_HEIGHT, LPCWSTR WINDOW_NAME, LPCWSTR CLASS_NAME, WNDPROC WindowProc)
{
	this->SCREEN_WIDTH = SCREEN_WIDTH;
	this->SCREEN_HEIGHT = SCREEN_HEIGHT;
	this->WINDOW_NAME = WINDOW_NAME;
	this->CLASS_NAME = CLASS_NAME;

	this->hInstance = GetModuleHandle(NULL);
	this->wc = CreateWindowClass(L"WindowClass", WindowProc);

	this->hWnd = Create();
	ShowWindow(hWnd, 10);
}

HWND& GameWindow::Create()
{
	HWND hwnd = CreateWindowEx(0,
		wc.lpszClassName,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		20,
		20,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	return hwnd;
}

HWND& GameWindow::CreateBorderless()
{
	HWND hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		wc.lpszClassName,
		WINDOW_NAME,
		WS_POPUP,
		20,
		20,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	return hwnd;
}

WNDCLASSEX& GameWindow::CreateWindowClass(LPCWSTR CLASS_NAME, WNDPROC &WindowProc)
{
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = CLASS_NAME;

	RegisterClassEx(&wc);

	return wc;
}

HWND& GameWindow::GetHWND()
{
	return hWnd;
}