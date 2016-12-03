#include "Graphics.h"

Graphics::Graphics()
{ }

void Graphics::Init(HWND &hWnd)
{
	backbufferWidth = options.resolutionX;
	backbufferHeight = options.resolutionY;

	this->hWnd = hWnd;

	RECT rect;
	GetWindowRect(hWnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	if (!CreateDevice()) { exit(0); }
	if (!CreateSwapChain(this->hWnd, width, height, 60, false)) { exit(0); }
	if (!CreateDepthBuffer(width, height)) { exit(0); }

	CreateRasterizerState();
}

bool Graphics::CreateDevice()
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
bool Graphics::CreateSwapChain(HWND hWnd, int width, int height, int rate, bool fullscreen)
{
	DXGI_SWAP_CHAIN_DESC desc = DXGI_SWAP_CHAIN_DESC();

	desc.BufferCount = 1;														// one back buffer
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;					// use 32-bit color, srgb: lineáris interpolációval exponenciális helyett
	desc.BufferDesc.Width = 0;													// set the back buffer width
	desc.BufferDesc.Height = 0;													// set the back buffer height
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
bool Graphics::CreateDepthBuffer(int width, int height)
{
	// create the depth buffer texture
	D3D11_TEXTURE2D_DESC texd;
	ZeroMemory(&texd, sizeof(texd));

	texd.Width = width;
	texd.Height = height;
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
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice = 0;

	hr = dev->CreateDepthStencilView(pDepthBuffer, &dsvd, &zbuffer);

	if (FAILED(hr))
	{
		std::cerr << "Depth stencil buffer not created";
	}

	return true;
}
void Graphics::CleanD3D()
{
	swapchain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode

	// close and release all existing COM objects
	zbuffer->Release();
	swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();
}

void Graphics::CreateRasterizerState()
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
void Graphics::CreateViewport()
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
void Graphics::Begin()
{
	CreateViewport();

	devcon->RSSetState(g_pRasterState);

	float clearColor[4] = { 0.0f, 0.2f, 0.4f, 1.0f };

	devcon->OMSetRenderTargets(1, &backbuffer, zbuffer);

	// clear the back buffer to a deep blue
	devcon->ClearRenderTargetView(backbuffer, clearColor);

	// clear the depth buffer
	devcon->ClearDepthStencilView(zbuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
void Graphics::Begin(float r, float g, float b)
{
	CreateViewport();

	devcon->RSSetState(g_pRasterState);

	float clearColor[4] = { r, g, b, 1.0f };

	devcon->OMSetRenderTargets(1, &backbuffer, zbuffer);

	// clear the back buffer to a deep blue
	devcon->ClearRenderTargetView(backbuffer, clearColor);

	// clear the depth buffer
	devcon->ClearDepthStencilView(zbuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
void Graphics::End()
{
	swapchain->Present(0, 0);
	devcon->ClearState();
}

ID3D11Device* Graphics::GetDevice()
{
	return dev;
}

ID3D11DeviceContext* Graphics::GetDeviceContext()
{
	return devcon;
}

GraphicsOptions* Graphics::GetGraphicsOptions()
{
	return &options;
}

HWND& Graphics::GetHWND()
{
	return hWnd;
}

int Graphics::GetWindowWidth()
{
	return 0;
}

int Graphics::GetWindowHeight()
{
	return 0;
}

bool Graphics::IsWindowActive()
{
	if (GetActiveWindow() == hWnd)
	{
		return true;
	}
	else
	{
		return false;
	}
}
