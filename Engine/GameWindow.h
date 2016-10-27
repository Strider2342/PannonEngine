#pragma once
#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>

#define LEAN_AND_MEAN
#define VC_EXTRALEAN

class GameWindow
{
private:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	LPCWSTR WINDOW_NAME;
	LPCWSTR CLASS_NAME;

	HINSTANCE hInstance;
	HWND hWnd;
	WNDCLASSEX wc;

public:
	GameWindow();
	GameWindow(int SCREEN_WIDTH, int SCREEN_HEIGHT, LPCWSTR WINDOW_NAME, LPCWSTR CLASS_NAME, WNDPROC WindowProc);

	HWND& Create();
	HWND& CreateBorderless();

	WNDCLASSEX& CreateWindowClass(LPCWSTR CLASS_NAME, WNDPROC &WindowProc);

	// get
	HWND& GetHWND();
};