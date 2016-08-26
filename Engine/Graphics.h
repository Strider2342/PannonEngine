#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include "GraphicsOptions.h"
#include "GameWindow.h"

class Graphics
{
private:
	GraphicsOptions options;
	GameWindow window;

	IDXGISwapChain *swapchain = nullptr;             // the pointer to the swap chain interface
	ID3D11Device *dev = nullptr;                     // the pointer to our Direct3D device interface
	ID3D11DeviceContext *devcon = nullptr;           // the pointer to our Direct3D device context
	ID3D11RenderTargetView *backbuffer = nullptr;    // the pointer to our back buffer
	ID3D11DepthStencilView *zbuffer = nullptr;       // the pointer to our depth buffer

	ID3D11Texture2D *pDepthBuffer;
	ID3D11Texture2D *pBackBuffer;

	ID3D11RasterizerState * g_pRasterState = nullptr;

	HWND hWnd;

	unsigned int backbufferWidth;
	unsigned int backbufferHeight;

public:
	Graphics();

	void Init();
	void InitD3D();

	bool CreateDevice();
	bool CreateSwapChain(HWND hWnd, int width, int height, int rate, bool fullscreen);
	bool CreateDepthBuffer();
	void CleanD3D();

	void CreateRasterizerState();
	void CreateViewport();
	void Begin();
	void End();
};