#pragma once
#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <dxgi.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "GraphicsOptions.h"
#include "EditorWindow.h"

class EditorGraphics
{
private:
	GraphicsOptions options;
	
	// window
	LPCWSTR WINDOW_NAME;
	LPCWSTR CLASS_NAME;

	HINSTANCE hInstance;
	HWND hWnd;
	WNDCLASSEX wc;

	// D3D
	IDXGISwapChain *swapchain = nullptr;             // the pointer to the swap chain interface
	ID3D11Device *dev = nullptr;                     // the pointer to our Direct3D device interface
	ID3D11DeviceContext *devcon = nullptr;           // the pointer to our Direct3D device context
	ID3D11RenderTargetView *backbuffer = nullptr;    // the pointer to our back buffer
	ID3D11DepthStencilView *zbuffer = nullptr;       // the pointer to our depth buffer

	ID3D11Texture2D *pDepthBuffer;
	ID3D11Texture2D *pBackBuffer;

	ID3D11RasterizerState * g_pRasterState = nullptr;

	unsigned int backbufferWidth;
	unsigned int backbufferHeight;

public:
	EditorGraphics();

	void Init();

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// window
	HWND& CreateWnd();
	HWND& CreateBorderless();

	WNDCLASSEX& CreateWindowClass();

	// D3D
	bool CreateDevice();
	bool CreateSwapChain(HWND hWnd, int width, int height, int rate, bool fullscreen);
	bool CreateDepthBuffer();
	void CleanD3D();

	void CreateRasterizerState();
	void CreateViewport();
	
	static void Resize(int width, int height);
	
	void Begin();
	void End();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();
	GraphicsOptions* GetGraphicsOptions();
	HWND& GetHWND();
};