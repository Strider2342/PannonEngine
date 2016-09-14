#pragma once
#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"

#define LEAN_AND_MEAN
#define VC_EXTRALEAN

class EditorWindow
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
	EditorWindow();
	EditorWindow(int SCREEN_WIDTH, int SCREEN_HEIGHT, LPCWSTR WINDOW_NAME, LPCWSTR CLASS_NAME);

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	HWND& Create();
	HWND& CreateBorderless();

	WNDCLASSEX& CreateWindowClass(LPCWSTR CLASS_NAME);

	// get
	HWND& GetHWND();
};