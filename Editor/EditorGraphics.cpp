#include "EditorGraphics.h"

EditorGraphics::EditorGraphics()
{ }

void EditorGraphics::Init()
{
	backbufferWidth = options.resolutionX;
	backbufferHeight = options.resolutionY;

	// window
	WINDOW_NAME = L"Pannon Editor";
	CLASS_NAME = L"Pannon Window Class";
	this->hInstance = GetModuleHandle(NULL);
	this->wc = CreateWindowClass();
	this->hWnd = CreateWnd();
	ShowWindow(hWnd, 10);

	if (!CreateDevice()) { exit(0); }
	if (!CreateSwapChain(hWnd, backbufferWidth, backbufferHeight, 60, false)) { exit(0); }
	if (!CreateDepthBuffer()) { exit(0); }

	CreateRasterizerState();
}

LRESULT CALLBACK EditorGraphics::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplDX11_WndProcHandler(hWnd, message, wParam, lParam))
		return true;
	switch (message)
	{
	case WM_SIZE: {
		ImGui_ImplDX11_InvalidateDeviceObjects();

		Resize((int)LOWORD(wParam), (int)HIWORD(lParam));

		ImGuiIO &io = ImGui::GetIO();
		io.DisplaySize.x = LOWORD(wParam);
		io.DisplaySize.y = HIWORD(lParam);

		ImGui_ImplDX11_CreateDeviceObjects();
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_KEYDOWN:
	{
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

HWND& EditorGraphics::CreateWnd()
{
	HWND hwnd = CreateWindowEx(0,
		wc.lpszClassName,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		300,
		300,
		options.resolutionX,
		options.resolutionY,
		NULL,
		NULL,
		hInstance,
		NULL);

	return hwnd;
}
HWND& EditorGraphics::CreateBorderless()
{
	HWND hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		wc.lpszClassName,
		WINDOW_NAME,
		WS_POPUP,
		300,
		300,
		options.resolutionX,
		options.resolutionY,
		NULL,
		NULL,
		hInstance,
		NULL);

	return hwnd;
}
WNDCLASSEX& EditorGraphics::CreateWindowClass()
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

bool EditorGraphics::CreateDevice()
{
	DWORD createDeviceFlags = 0;
#if _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, createDeviceFlags, 0, 0, D3D11_SDK_VERSION, &dev, &featureLevel, &devcon);

	if (SUCCEEDED(hr))
		return true;
	else
	{
		std::cerr << "Device not created.";
		return false;
	}
}
bool EditorGraphics::CreateSwapChain(HWND hWnd, int width, int height, int rate, bool fullscreen)
{
	DXGI_SWAP_CHAIN_DESC desc = DXGI_SWAP_CHAIN_DESC();

	desc.BufferCount = 1;														// one back buffer
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;					// use 32-bit color, srgb: lineáris interpolációval exponenciális helyett
	desc.BufferDesc.Width = width;												// set the back buffer width
	desc.BufferDesc.Height = height;											// set the back buffer height
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;					// set the scaling mode
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	// set the scanline drawing mode
	desc.BufferDesc.RefreshRate.Numerator = rate;								// set the screen's maximum refresh rate
	desc.BufferDesc.RefreshRate.Denominator = 1;								// set the screen's minimum refresh rate
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;							// how swap chain is to be used
	desc.OutputWindow = hWnd;													// the window to be used
	desc.SampleDesc.Count = 1;													// how many multisamples
	desc.SampleDesc.Quality = 0;
	desc.Windowed = !fullscreen;												// windowed/full-screen mode
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;						// allow full-screen switching

	IDXGIFactory *factory = nullptr;
	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	HRESULT hr = factory->CreateSwapChain(dev, &desc, &swapchain);

	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&pBackBuffer);
	dev->CreateRenderTargetView(pBackBuffer, nullptr, &backbuffer);
	pBackBuffer->Release();

	if (SUCCEEDED(hr))
		return true;
	else
	{
		std::cerr << "Swap chain not created.";
		return false;
	}
}
bool EditorGraphics::CreateDepthBuffer()
{
	// create the depth buffer texture
	D3D11_TEXTURE2D_DESC texd;
	ZeroMemory(&texd, sizeof(texd));

	texd.Width = backbufferWidth;
	texd.Height = backbufferHeight;
	texd.MipLevels = 1;
	texd.ArraySize = 1;
	texd.Format = DXGI_FORMAT_D32_FLOAT;
	texd.SampleDesc.Count = 1;
	texd.SampleDesc.Quality = 0;
	texd.Usage = D3D11_USAGE_DEFAULT;
	texd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	texd.CPUAccessFlags = 0;
	texd.MiscFlags = 0;

	HRESULT hr = dev->CreateTexture2D(&texd, NULL, &pDepthBuffer);

	if (FAILED(hr))
	{
		std::cerr << "Depth buffer texture not created";
	}

	// create the depth buffer
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));

	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	dsvd.Texture2D.MipSlice = 0;;

	hr = dev->CreateDepthStencilView(pDepthBuffer, &dsvd, &zbuffer);

	if (FAILED(hr))
	{
		std::cerr << "Depth stencil buffer not created";
	}

	return true;
}
void EditorGraphics::CleanD3D()
{
	swapchain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode

	// close and release all existing COM objects
	zbuffer->Release();
	swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();
}

void EditorGraphics::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterizerState;
	rasterizerState.FillMode = D3D11_FILL_SOLID;
	rasterizerState.CullMode = D3D11_CULL_NONE;
	rasterizerState.FrontCounterClockwise = true;
	rasterizerState.DepthBias = false;
	rasterizerState.DepthBiasClamp = 0;
	rasterizerState.SlopeScaledDepthBias = 0;
	rasterizerState.DepthClipEnable = true;
	rasterizerState.ScissorEnable = false;
	rasterizerState.MultisampleEnable = false;
	rasterizerState.AntialiasedLineEnable = false;
	dev->CreateRasterizerState(&rasterizerState, &g_pRasterState);
}
void EditorGraphics::CreateViewport()
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)backbufferWidth;
	viewport.Height = (float)backbufferHeight;
	viewport.MinDepth = 0;    // the closest an object can be on the depth buffer is 0.0
	viewport.MaxDepth = 1;    // the farthest an object can be on the depth buffer is 1.0	
	devcon->RSSetViewports(1, &viewport);
}
void EditorGraphics::Resize(int width, int height)
{
	// To be done
}
void EditorGraphics::Begin()
{
	CreateViewport();

	devcon->RSSetState(g_pRasterState);

	float clearColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };

	devcon->OMSetRenderTargets(1, &backbuffer, zbuffer);

	// clear the back buffer to a deep blue
	devcon->ClearRenderTargetView(backbuffer, clearColor);

	// clear the depth buffer
	devcon->ClearDepthStencilView(zbuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
void EditorGraphics::End()
{
	swapchain->Present(0, 0);
	devcon->ClearState();
}

ID3D11Device* EditorGraphics::GetDevice()
{
	return dev;
}

ID3D11DeviceContext* EditorGraphics::GetDeviceContext()
{
	return devcon;
}

GraphicsOptions* EditorGraphics::GetGraphicsOptions()
{
	return &options;
}

HWND& EditorGraphics::GetHWND()
{
	return hWnd;
}
